#ifndef SIMPLEDB_BPTREE_HPP_
#define SIMPLEDB_BPTREE_HPP_

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using std::array;
using std::fill;
using std::function;
using std::ios;
using std::make_shared;
using std::pair;
using std::shared_ptr;

template <class T>
class Property
{
public:
    Property() {}
    explicit Property(const T &f) { value = f; }
    virtual ~Property() {}

    virtual auto operator=(const T &f) -> T & { return value = f; }
    virtual auto operator()() const -> const T & { return value; }
    virtual auto itself() -> T & { return value; }

protected:
    T value;
};

template <class T, int S>
class ArrayProperty
{
public:
    ArrayProperty() {}
    explicit ArrayProperty(const T &f) { value.fill(f); }
    explicit ArrayProperty(const array<T, S> &f) { value = f; }
    virtual ~ArrayProperty() {}

    virtual auto operator[](int i) -> T & { return value[i]; }
    virtual auto operator()() const -> const array<T, S> & { return value; }
    virtual auto itself() -> array<T, S> & { return value; }
    virtual void set(int i, const T &f) { value[i] = f; }

protected:
    array<T, S> value;
};

class Pager : protected std::fstream
{
public:
    explicit Pager(std::string file_name, bool trunc = false)
        : std::fstream(file_name.data(), ios::in | ios::out | ios::binary)
    {
        empty = false;
        fileName = file_name;
        if (!good() || trunc)
        {
            empty = true;
            open(file_name.data(),
                 ios::in | ios::out | ios::trunc | ios::binary);
        }
    }
    ~Pager() { close(); }
    inline bool is_empty() { return empty; }
    template <class Register>
    void save(const int64_t &n, Register *reg)
    {
        clear();
        //off: offset value
        //way: object of type ios_base::seekdir (begin current or end)
        seekp(n * sizeof(Register), std::ios::beg);
        //pointer to an array of at least n characters
        //reinterpret_cast convert any pointer object to char pointer
        //(work with bits)
        write(reinterpret_cast<char *>(reg), sizeof(*reg));
    }
    template <class Register>
    bool recover(const int64_t &n, Register *reg)
    {
        clear();
        seekg(n * sizeof(Register), std::ios::beg);
        read(reinterpret_cast<char *>(reg), sizeof(*reg));
        return gcount() > 0;
    }

    template <class Register>
    void erase(const int64_t &n)
    {
        clear();
        char mark = 'N';
        seekg(n * sizeof(Register), std::ios::beg);
        write(&mark, 1);
    }

private:
    std::string fileName;
    bool empty;
};

template <class T, int ORDER>
class Node
{
    template <class A, int B>
    friend class Iterator;
    template <class A, int B>
    friend class bptree;

public:
    Node()
    {
        this->page_id = 0;
        this->count = 0;
        this->right = 0;
    }
    explicit Node(int64_t page_id)
    {
        this->page_id = page_id;
        this->count = 0;
        this->right = 0;
    }

protected:
    Property<int64_t> page_id{-1};
    Property<int64_t> count{0};
    Property<int64_t> right{0};
    ArrayProperty<T, ORDER + 1> data{};
    ArrayProperty<int64_t, ORDER + 2> children{0};

    void insert_in_node(int64_t pos, const T &value)
    {
        auto j = count();
        while (j > pos)
        {
            data[j] = data[j - 1];
            children[j + 1] = children[j];
            j--;
        }
        data[j] = value;
        children[j + 1] = children[j];
        count = count() + 1;
    }
    void delete_in_node(int64_t pos)
    {
        for (auto i = pos; i < count; i++)
        {
            data[i] = data[i + 1];
            children[i + 1] = children[i + 2];
        }
        count--;
    }
    bool is_overflow() const { return count() > ORDER; }
    bool is_underflow() const { return count() < floor(ORDER / 2.0); }
};

template <class T, int B>
class Iterator
{
    using node = Node<T, B>;
    template <class X, int Y>
    friend class bptree;

public:
    Iterator() {}
    Iterator(const Iterator &that) // FIXME: explicit
    {
        this->current_pos = that.current_pos();
        this->index = that.index();
        this->pager = that.pager;
    }
    explicit Iterator(shared_ptr<Pager> pager) : pager{pager} {}

    auto operator*() -> T
    {
        return current_pos.itself().get()->data()[index()];
    }
    auto operator++() -> Iterator &
    {
        if (index() < current_pos()->count() - 1)
        {
            index = index() + 1;
        }
        else
        {
            index = 0;
            auto that = make_shared<node>(-1);
            if (current_pos()->right() == 0)
            {
                current_pos = that;
            }
            else
            {
                this->pager->recover(
                    current_pos()->right(), current_pos.itself().get());
            }
        }
        return *this;
    }
    auto operator++(int) -> Iterator
    {
        auto temp = *this;
        ++*this;
        return temp;
    }
    auto operator=(const Iterator &that) -> Iterator &
    {
        this->current_pos = that.current_pos();
        this->index = that.index();
        this->pager = that.pager;
        return *this;
    }
    bool operator!=(const Iterator &that) const
    {
        if (this->current_pos()->page_id() == that.current_pos()->page_id())
        {
            auto this_n = this->current_pos();
            auto that_n = that.current_pos();
            return !(this_n->data()[index()] == that_n->data()[that.index()]);
        }
        return true;
    }

protected:
    Property<int64_t> index{0};
    Property<shared_ptr<node>> current_pos;

private:
    shared_ptr<Pager> pager;
};

template <class T, int ORDER = 3>
class bptree
{
    using node = Node<T, ORDER>;
    using iterator = Iterator<T, ORDER>;
    enum class bptree_state
    {
        BT_OVERFLOW, // TODO:
        BT_UNDERFLOW,
        OK,
    };
    struct Header
    {
        int64_t root_id = 1;
        int64_t count = 0;
    };

public:
    explicit bptree(shared_ptr<Pager> pager)
    {
        this->pager = pager;
        if (pager->is_empty())
        {
            node root(header->root_id);
            pager->save(root.page_id(), &root);
            header->count++;
            pager->save(0, header.get());
        }
        else
        {
            pager->recover(0, header.get());
        }
    }
    auto begin() -> iterator
    {
        auto root = read_node(header->root_id);
        while (root->children()[0] != 0)
        {
            auto id = root->children()[0];
            root = read_node(id);
        }
        iterator it(pager);
        it.current_pos = root;
        return it;
    }
    auto find(const T &value) -> iterator
    {
        auto root = read_node(header->root_id);
        auto it = find_helper(value, root);
        return *it == value ? it : end();
    }
    auto find_geq(const T &value) -> iterator
    {
        auto root = read_node(header->root_id);
        auto it = find_helper(value, root);
        return it;
    }

    auto end() -> iterator
    {
        auto end = make_shared<node>(-1);
        iterator it(pager);
        it.current_pos = end;
        return it;
    }
    void insert(const T &value)
    {
        auto root = read_node(header->root_id);
        auto state = insert(root, value);
        if (state == bptree_state::BT_OVERFLOW)
        {
            auto node_in_overflow = read_node(header->root_id);
            auto child1 = new_node();
            auto child2 = new_node();

            auto pos = 0;
            auto iter = 0;
            auto i = 0;
            for (i = 0; iter < ceil(ORDER / 2.0); i++)
            {
                child1->children.set(i, node_in_overflow->children()[iter]);
                child1->data.set(i, node_in_overflow->data()[iter]);
                child1->count = child1->count() + 1; // FIXME:
                iter++;
            }
            child1->children.set(i, node_in_overflow->children()[iter]);

            node_in_overflow->data.set(0, node_in_overflow->data()[iter]);
            child1->right = child2->page_id();

            if (node_in_overflow->children()[0] != 0)
            {
                iter++;
            }

            for (i = 0; iter < ORDER + 1; i++)
            {
                child2->children.set(i, node_in_overflow->children()[iter]);
                child2->data.set(i, node_in_overflow->data()[iter]);
                child2->count = child2->count() + 1; // FIXME:
                iter++;
            }
            child2->children.set(i, node_in_overflow->children()[iter]);

            node_in_overflow->children.set(0, child1->page_id());
            node_in_overflow->children.set(1, child2->page_id());
            node_in_overflow->count = 1;

            write_node(node_in_overflow->page_id(), node_in_overflow);
            write_node(child1->page_id(), child1);
            write_node(child2->page_id(), child2);
        }
    }
    void print_tree()
    {
        auto root = read_node(header->root_id);
        print_tree(root, 0);
        std::cout << "________________________\n";
    }
    void print_tree(shared_ptr<node> ptr, int level)
    {
        int i;
        for (i = ptr->count() - 1; i >= 0; i--)
        {
            if (ptr->children()[i + 1])
            {
                auto child = read_node(ptr->children()[i + 1]);
                print_tree(child, level + 1);
            }
            for (int k = 0; k < level; k++)
            {
                std::cout << "    ";
            }
            std::cout << ptr->data()[i].key << "\n";
        }
        if (ptr->children()[i + 1])
        {
            auto child = read_node(ptr->children()[i + 1]);
            print_tree(child, level + 1);
        }
    }

private:
    shared_ptr<Pager> pager;
    shared_ptr<Header> header = make_shared<Header>();
    auto find_helper(const T &value, shared_ptr<node> root) -> iterator
    {
        auto pos = 0;
        if (root->children()[0] != 0)
        {
            while (pos < root->count() && root->data()[pos] <= value)
            {
                pos++;
            }
            auto child = read_node(root->children()[pos]);
            return find_helper(value, child);
        }
        else
        {
            while (pos < root->count() && root->data()[pos] < value)
            {
                pos++;
            }
            iterator it(pager);
            it.current_pos = root;
            it.index = pos;
            if (pos == root->count())
            {
                it++;
            }
            return it;
        }
    };

    void write_node(int64_t id, shared_ptr<node> n_ptr)
    {
        pager->save(id, n_ptr.get());
    }
    auto read_node(int64_t id) -> shared_ptr<node>
    {
        auto ret = make_shared<node>(-1);
        pager->recover(id, ret.get());
        return ret;
    }
    auto new_node() -> shared_ptr<node>
    {
        header->count++;
        auto ret = make_shared<node>(header->count);
        pager->save(0, header.get());
        return ret;
    }
    auto insert(shared_ptr<node> n, const T &value) -> bptree_state
    {
        auto pos = 0;
        while (pos < n->count() && n->data()[pos] < value)
        {
            pos++;
        }
        if (n->children()[pos] != 0)
        {
            auto id = n->children()[pos];
            auto child = read_node(id);
            auto state = insert(child, value);
            if (state == bptree_state::BT_OVERFLOW)
            {
                auto node_in_overflow = read_node(n->children()[pos]);
                auto child1 = node_in_overflow;
                child1->count = 0;
                auto child2 = new_node();

                auto iter = 0;
                auto i = 0;
                for (i = 0; iter < ceil(ORDER / 2.0); i++)
                {
                    child1->children.set(i, node_in_overflow->children()[iter]);
                    child1->data.set(i, node_in_overflow->data()[iter]);
                    child1->count = child1->count() + 1; // FIXME:
                    iter++;
                }
                child1->children.set(i, node_in_overflow->children()[iter]);

                n->insert_in_node(pos, node_in_overflow->data()[iter]);
                if (node_in_overflow->children()[0] != 0)
                {
                    iter++;
                }
                else
                {
                    child2->right = child1->right();
                    child1->right = child2->page_id();
                    n->children.set(pos + 1, child2->page_id());
                }
                for (i = 0; iter < ORDER + 1; i++)
                {
                    child2->children.set(i, node_in_overflow->children()[iter]);
                    child2->data.set(i, node_in_overflow->data()[iter]);
                    child2->count = child2->count() + 1; // FIXME:
                    iter++;
                }
                child2->children.set(i, node_in_overflow->children()[iter]);
                n->children.set(pos, child1->page_id());
                n->children.set(pos + 1, child2->page_id());
                write_node(n->page_id(), n);
                write_node(child1->page_id(), child1);
                write_node(child2->page_id(), child2);
            }
        }
        else
        {
            n->insert_in_node(pos, value);
            write_node(n->page_id(), n);
        }
        return n->is_overflow() ? bptree_state::BT_OVERFLOW : bptree_state::OK;
    }
};

#endif //SIMPLEDB_BPTREE_HPP_
