//
// Created by jaoks on 5/17/20.
//

#ifndef SIMPLEDB_BTREE_SRC_BTREE_H_
#define SIMPLEDB_BTREE_SRC_BTREE_H_

#include <array>
#include <cmath>
#include <memory>
#include "./pagemanager.h"

using std::array;
using std::fill;

template <class T, int BTREE_ORDER>
class Node
{
private:
    int64_t page_id_ = -1;
    int64_t count_ = 0;
    int64_t right_ = 0;
    array<T, BTREE_ORDER + 1> data_;
    array<int64_t, BTREE_ORDER + 2> children_;

public:
    Node() {}
    explicit Node(int64_t page_id)
        : page_id_{page_id}, count_{0}, children_{} {}

    void insert_in_node(int pos, const T &value)
    {
        auto j = count_;
        while (j > pos)
        {
            data_[j] = data_[j - 1];
            children_[j + 1] = children_[j];
            j--;
        }
        data_[j] = value;
        children_[j + 1] = children_[j];
        count_++;
    }
    void delete_in_node(int pos)
    {
        for (auto i = pos; i < count_; i++)
        {
            data_[i] = data_[i + 1];
            children_[i + 1] = children_[i + 2];
        }
        count_--;
    }

    bool is_overflow() const { return count_ > BTREE_ORDER; }
    bool is_underflow() const { return count_ < floor(BTREE_ORDER / 2.0); }

    auto page_id() const -> int64_t { return page_id_; }
    auto count() const -> int64_t { return count_; }
    auto right() const -> int64_t { return right_; }
    auto data(int16_t i) const -> T { return data_[i]; }
    auto children(int16_t i) const -> int64_t { return children_[i]; }

    void set_page_id(int64_t page_id) { page_id_ = page_id; }
    void set_count(int64_t count) { count_ = count; }
    void count_incr() { count_++; }
    void set_right(int64_t right) { right_ = right; }
    void set_data(int16_t i, T datum) { data_[i] = datum; }
    void set_children(int16_t i, int64_t child) { children_[i] = child; }
};

template <class T, int B>
class Iterator
{
public:
    typedef Node<T, B> node;
    int index = 0;
    node currentPosition;

    Iterator() {}

    explicit Iterator(std::shared_ptr<pagemanager> pm) : pm{pm} {}

    T operator*() { return currentPosition.data(index); }

    Iterator &operator++()
    {
        if (index < currentPosition.count() - 1)
        {
            index++;
        }
        else
        {
            index = 0;
            node aux(-1);
            if (currentPosition.right() == 0)
            {
                currentPosition = aux;
            }
            else
            {
                this->pm->recover(currentPosition.right(), currentPosition);
            }
        }
        return *this;
    }

    Iterator &operator=(const Iterator &copy)
    {
        this->currentPosition = copy.currentPosition;
        this->index = copy.index;
        this->pm = copy.pm;
        return *this;
    }

    Iterator(const Iterator &copy)
    {
        this->currentPosition = copy.currentPosition;
        this->index = copy.index;
        this->pm = copy.pm;
    }

    bool operator!=(const Iterator &other) const
    {
        if (this->currentPosition.page_id() == other.currentPosition.page_id())
        {
            return !(this->currentPosition.data(index) ==
                     other.currentPosition.data(other.index));
        }
        return true;
    }

    void set_position(node position) { currentPosition = position; }
    void set_index(int64_t idx) { index = idx; }

private:
    std::shared_ptr<pagemanager> pm;
};

template <class T, int BTREE_ORDER = 3>
class btree
{
public:
    typedef Node<T, BTREE_ORDER> node;
    typedef Iterator<T, BTREE_ORDER> iterator;
    struct Metadata
    {
        int64_t root_id = 1;
        int64_t count = 0;
    } header;

    auto begin() -> iterator
    {
        node root = read_node(header.root_id);
        while (root.children(0) != 0)
        {
            int64_t page_id = root.children(0);
            root = read_node(page_id);
        }
        iterator it(pm);
        it.set_position(root);
        return it;
    }

    auto find(const T &what) -> iterator // TODO:
    {
        std::function<iterator(const T &, const node &)>
            find_helper = [&](const T &what, const node &other) -> iterator {
            auto pos = 0;
            if (other.children(0) != 0)
            {
                while (pos < other.count() && other.data(pos) <= what)
                {
                    pos++;
                }
                auto child = read_node(other.children(pos));
                return find_helper(what, child);
            }
            else
            {
                while (pos < other.count() && other.data(pos) < what)
                {
                    pos++;
                }
                iterator it(pm);
                it.set_position(other);
                it.set_index(pos);
                return it;
            }
        };
        auto root = read_node(header.root_id);
        auto it = find_helper(what, root);
        return *it == what ? it : end();
    }

    auto end() -> iterator
    {
        node end_node(-1);
        iterator it(pm);
        it.set_position(end_node);
        return it;
    }

    enum state
    {
        BT_OVERFLOW,
        BT_UNDERFLOW,
        NORMAL,
    };

private:
    std::shared_ptr<pagemanager> pm;

public:
    explicit btree(std::shared_ptr<pagemanager> pm) : pm{pm}
    {
        if (pm->is_empty())
        {
            node root{header.root_id};
            pm->save(root.page_id(), root);
            header.count++;
            pm->save(0, header);
        }
        else
        {
            pm->recover(0, header);
        }
    }

    node new_node()
    {
        header.count++;
        node ret(header.count);
        pm->save(0, header);
        return ret;
    }

    node read_node(int64_t page_id)
    {
        node n(-1);
        pm->recover(page_id, n);
        return n;
    }

    void write_node(int64_t page_id, node n) { pm->save(page_id, n); }

    void insert(const T &value)
    {
        auto root = read_node(header.root_id);
        auto state = insert(root, value);
        if (state == BT_OVERFLOW)
        {
            split_root();
        }
    }

    int insert(node &ptr, const T &value)
    {
        auto pos = 0;
        while (pos < ptr.count() && ptr.data(pos) < value)
        {
            pos++;
        }
        if (ptr.children(pos) != 0)
        {
            auto page_id = ptr.children(pos);
            auto child = read_node(page_id);
            auto state = insert(child, value);
            if (state == BT_OVERFLOW)
            {
                split(ptr, pos);
            }
        }
        else
        {
            ptr.insert_in_node(pos, value);
            write_node(ptr.page_id(), ptr);
        }
        return ptr.is_overflow() ? BT_OVERFLOW : NORMAL;
    }

    void split(node &parent, int pos)
    {
        auto node_in_overflow = this->read_node(parent.children(pos));
        auto child1 = node_in_overflow;
        child1.set_count(0);
        auto child2 = this->new_node();

        auto iter = 0;
        auto i = 0;
        for (i = 0; iter < ceil(BTREE_ORDER / 2.0); i++)
        {
            child1.set_children(i, node_in_overflow.children(iter));
            child1.set_data(i, node_in_overflow.data(iter));
            child1.count_incr();
            iter++;
        }
        child1.set_children(i, node_in_overflow.children(iter));
        parent.insert_in_node(pos, node_in_overflow.data(iter));
        if (node_in_overflow.children(0) != 0)
        {
            iter++;
        }
        else
        {
            child2.set_right(child1.right());
            child1.set_right(child2.page_id());
            parent.set_children(pos + 1, child2.page_id());
        }
        for (i = 0; iter < BTREE_ORDER + 1; i++)
        {
            child2.set_children(i, node_in_overflow.children(iter));
            child2.set_data(i, node_in_overflow.data(iter));
            child2.count_incr();
            iter++;
        }
        child2.set_children(i, node_in_overflow.children(iter));
        parent.set_children(pos, child1.page_id());
        parent.set_children(pos + 1, child2.page_id());
        write_node(parent.page_id(), parent);
        write_node(child1.page_id(), child1);
        write_node(child2.page_id(), child2);
    }

    void split_root()
    {
        auto node_in_overflow = this->read_node(this->header.root_id);
        auto child1 = this->new_node();
        auto child2 = this->new_node();

        auto pos = 0;
        auto iter = 0;
        auto i = 0;
        for (i = 0; iter < ceil(BTREE_ORDER / 2.0); i++)
        {
            child1.set_children(i, node_in_overflow.children(iter));
            child1.set_data(i, node_in_overflow.data(iter));
            child1.count_incr();
            iter++;
        }
        child1.set_children(i, node_in_overflow.children(iter));

        node_in_overflow.set_data(0, node_in_overflow.data(iter));

        child1.set_right(child2.page_id());

        if (node_in_overflow.children(0) != 0)
        {
            iter++; // the middle element
        }

        for (i = 0; iter < BTREE_ORDER + 1; i++)
        {
            child2.set_children(i, node_in_overflow.children(iter));
            child2.set_data(i, node_in_overflow.data(iter));
            child2.count_incr();
            iter++;
        }
        child2.set_children(i, node_in_overflow.children(iter));

        node_in_overflow.set_children(0, child1.page_id());
        node_in_overflow.set_children(1, child2.page_id());
        node_in_overflow.set_count(1);

        write_node(node_in_overflow.page_id(), node_in_overflow);
        write_node(child1.page_id(), child1);
        write_node(child2.page_id(), child2);
    }

    void remove(const T &value)
    {
        node root = read_node(header.root_id);
        int state = remove(root, value);
        ///root = read_node(header.root_id);
        if (state == BT_UNDERFLOW && root.count() == 0)
        {
            header.root_id = root.children(0);
            write_node(root.page_id(), root);
            pm->save(0, header);
        }
    }

    int remove(node &ptr, const T &value)
    {
        int pos = 0;
        while (pos < ptr.count() && ptr.data(pos) < value)
        {
            pos++;
        }
        if (ptr.children(pos) != 0)
        {
            if (ptr.data(pos) == value && pos != ptr.count())
            {
                node next = read_node(ptr.children(pos + 1));
                ptr.set_data(pos, succesor(next));
                write_node(ptr.page_id(), ptr);
                pos++;
            }
            node child = read_node(ptr.children(pos));
            int state = remove(child, value);
            if (state == BT_UNDERFLOW)
            {
                node node_in_underflow = child;
                bool can_steal = steal_sibling(node_in_underflow, ptr, pos);
                if (!can_steal)
                {
                    if (node_in_underflow.children(0) == 0)
                    { //si el underflow es leaf
                        merge_leaf(ptr, node_in_underflow, pos);
                    }
                    else
                    {
                        bool can_merge = merge_with_parent(ptr, node_in_underflow, pos);
                        if (!can_merge)
                            decrease_height(ptr, node_in_underflow, pos);
                    }
                }
            }
        }
        else if (ptr.data(pos) == value)
        {
            ptr.delete_in_node(pos);
            write_node(ptr.page_id(), ptr);
        }

        return ptr.is_underflow() ? BT_UNDERFLOW : NORMAL;
    }

    void decrease_height(node &ptr, node &node_in_underflow, int pos)
    {
        if (pos != ptr.count())
        {
            node child = read_node(ptr.children(pos));
            if (child.count() < floor(BTREE_ORDER / 2.0))
            {
                node sibling = read_node(ptr.children(pos + 1));
                sibling.insert_in_node(0, ptr.data(pos));
                int last = node_in_underflow.count();
                sibling.set_children(0, node_in_underflow.children(last));

                for (int i = last - 1; i >= 0; --i)
                {
                    sibling.insert_in_node(0, node_in_underflow.data(i));
                    sibling.children(0, node_in_underflow.children(i));
                }
                ptr.delete_in_node(pos);
                ptr.set_children(pos, sibling.page_id());
                write_node(sibling.page_id(), sibling);
                write_node(ptr.page_id(), ptr);
                return;
            }
        }
        node sibling = read_node(ptr.children(pos - 1));
        int last = sibling.count();
        sibling.insert_in_node(last, ptr.data(pos - 1));
        sibling.set_children(last + 1, node_in_underflow.children(0));
        for (int i = 0; i < node_in_underflow.count(); i++)
        {
            last = sibling.count();
            sibling.insert_in_node(last, node_in_underflow.data(i));
            sibling.set_children(last + 1, node_in_underflow.children(i + 1));
        }
        ptr.delete_in_node(pos - 1);
        ptr.set_children(pos - 1, sibling.page_id());

        write_node(sibling.page_id(), sibling);
        write_node(ptr.page_id(), ptr);
    }

    bool merge_with_parent(node &ptr, node &node_in_underflow, int pos)
    {
        if (pos != 0)
        {
            node sibling = read_node(ptr.children(pos - 1));
            if (sibling.count() - 1 >= floor(BTREE_ORDER / 2.0))
            {
                T jesus = ptr.data(pos - 1);
                node_in_underflow.insert_in_node(0, jesus);
                ptr.set_data(pos - 1, sibling.data(sibling.count() - 1));
                node_in_underflow
                    .set_children(0, sibling.children(sibling.count()));
                sibling.delete_in_node(sibling.count() - 1);
                write_node(sibling.page_id(), sibling);
                write_node(ptr.page_id(), ptr);
                write_node(node_in_underflow.page_id(), node_in_underflow);
                return true;
            }
        }
        else if (pos != BTREE_ORDER)
        {
            node sibling = read_node(ptr.children(pos + 1));
            if (sibling.count() - 1 >= floor(BTREE_ORDER / 2.0))
            {
                T jesus = ptr.data(pos);
                node_in_underflow.insert_in_node(0, jesus);
                ptr.data(pos, sibling.data(0));
                node_in_underflow.set_children(1, sibling.children(0));
                sibling.set_children(0, sibling.children(1));
                sibling.delete_in_node(0);

                write_node(sibling.page_id(), sibling);
                write_node(ptr.page_id(), ptr);
                write_node(node_in_underflow.page_id(), node_in_underflow);
                return true;
            }
        }
        return false;
    }

    void merge_leaf(node &ptr, node &node_in_underflow, int pos)
    {
        if (pos - 1 >= 0)
        { //right se une a left
            node sibling = read_node(ptr.children(pos - 1));
            for (int i = 0; i < node_in_underflow.count(); i++)
            {
                int pos_in = sibling.count();
                sibling.insert_in_node(pos_in, node_in_underflow.data(i));
            }
            sibling.set_right(node_in_underflow.right());
            ptr.delete_in_node(pos - 1);

            write_node(sibling.page_id(), sibling);
            write_node(ptr.page_id(), ptr);
        }
        else
        { //left se une a la right
            node sibling = read_node(ptr.children(1));
            for (int i = 0; i < sibling.count(); i++)
            {
                int pos_in = node_in_underflow.count();
                node_in_underflow.insert_in_node(pos_in, sibling.data(i));
            }
            node_in_underflow.set_right(sibling.right());
            ptr.delete_in_node(0);
            write_node(node_in_underflow.page_id(), node_in_underflow);
            write_node(ptr.page_id(), ptr);
        }
    }

    bool steal_sibling(node &node_in_underflow, node &ptr, int pos)
    {
        if (node_in_underflow.children(0) == 0)
        {
            if (pos != ptr.count())
            {
                node sibling = read_node(ptr.children(pos + 1));
                if (sibling.count() - 1 >= floor(BTREE_ORDER / 2.0))
                {
                    T jesus = sibling.data(0);
                    T jesus2 = sibling.data(1);
                    sibling.delete_in_node(0);
                    node_in_underflow.insert_in_node(sibling.count() - 1, jesus);
                    ptr.set_data(pos, jesus2);
                    write_node(sibling.page_id(), sibling);
                    write_node(node_in_underflow.page_id(), node_in_underflow);
                    write_node(ptr.page_id(), ptr);
                    return true;
                }
            }
            if (pos > 0)
            {
                node sibling = read_node(ptr.children(pos - 1));
                if (sibling.count() - 1 >= floor(BTREE_ORDER / 2.0))
                {
                    T jesus = sibling.data(sibling.count() - 1);
                    sibling.delete_in_node(sibling.count() - 1);
                    node_in_underflow.insert_in_node(0, jesus);
                    ptr.set_data(pos - 1, jesus);
                    write_node(sibling.page_id(), sibling);
                    write_node(node_in_underflow.page_id(), node_in_underflow);
                    write_node(ptr.page_id(), ptr);
                    return true;
                }
            }
        }
        return false;
    }

    T succesor(node &ptr)
    {
        while (ptr.children(0) != 0)
        {
            ptr = read_node(ptr.children(0));
        }
        if (ptr.count() == 1)
        {
            if (ptr.right() == -1)
                return NULL;
            ptr = read_node(ptr.right());
            return ptr.data(0);
        }
        else
        {
            return ptr.data(1);
        }
    }

    void print(std::ostream &out)
    {
        node root = read_node(header.root_id);
        print(root, 0, out);
    }

    void print(const node &ptr, int level, std::ostream &out)
    {
        int i;
        for (i = 0; i < ptr.count(); i++)
        {
            if (ptr.children(i))
            {
                node child = read_node(ptr.children(i));
                print(child, level + 1, out);
            }
            out << ptr.data(i);
        }
        if (ptr.children(i))
        {
            node child = read_node(ptr.children(i));
            print(child, level + 1, out);
        }
    }

    void print_tree()
    {
        node root = read_node(header.root_id);
        print_tree(root, 0);
        std::cout << "________________________\n";
    }

    void print_tree(const node &ptr, int level)
    {
        int i;
        for (i = ptr.count() - 1; i >= 0; i--)
        {
            if (ptr.children(i + 1))
            {
                node child = read_node(ptr.children(i + 1));
                print_tree(child, level + 1);
            }

            for (int k = 0; k < level; k++)
            {
                std::cout << "    ";
            }
            std::cout << ptr.data(i).key << "\n";
        }
        if (ptr.children(i + 1))
        {
            node child = read_node(ptr.children(i + 1));
            print_tree(child, level + 1);
        }
    }
};

#endif //SIMPLEDB_BTREE_SRC_BTREE_H_
