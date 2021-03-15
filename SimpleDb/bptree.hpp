#ifndef SIMPLEDB_BPTREE_HPP_
#define SIMPLEDB_BPTREE_HPP_

#include <fmt/color.h>
#include <fmt/core.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "util.hpp"

class Pager : protected std::fstream
{
    template <class A, int16_t B>
    friend class BPTree;
    template <class A, int16_t B>
    friend class Iterator;
    friend class Database;

public:
    Property<bool> empty;

    explicit Pager(std::string file_name, bool create = false)
        : std::fstream(file_name.data(),
                       std::ios::in | std::ios::out | std::ios::binary)
    {
        if (!create && !is_open())
        {
            throw file_not_exist(file_name);
        }
        if (!create && fail())
        {
            throw file_opening_error(file_name);
        }
        empty = false;
        if (create)
        {
            empty = true;
            open(file_name.data(),
                 std::ios::in | std::ios::out |
                     std::ios::trunc | std::ios::binary);
        }
    }
    ~Pager() { close(); }
    template <class Register>
    auto get_id(Register *reg) -> int64_t
    {
        // FIXME:
        seekg(0, std::ios::end);
        auto id = tellg() / sizeof(Register);
        return id;
    }

protected:
    template <class Register>
    void save(const int64_t &n, Register *reg)
    {
        clear();
        seekp(n * sizeof(Register), std::ios::beg);
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
        char mark = 'X';
        seekg(n * sizeof(Register), std::ios::beg);
        write(&mark, 1);
    }
};

template <class T, int16_t ORDER>
class Node
{
    template <class X, int16_t Y>
    friend class Iterator;
    template <class X, int16_t Y>
    friend class BPTree;

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

    void insert_InNode(int64_t pos, const T &value)
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

    void delete_InNode(int64_t pos)
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

    bool is_leaf() const { return children()[0] == 0; }
};

template <class T, int16_t ORDER>
class Iterator
{
    using node = Node<T, ORDER>;
    template <class X, int16_t Y>
    friend class BPTree;

public:
    Iterator() {}
    Iterator(const Iterator &that)
    {
        this->current_pos = that.current_pos();
        this->index = that.index();
        this->pager = that.pager;
    }
    explicit Iterator(std::shared_ptr<Pager> pager) : pager{pager} {}

    auto operator->() -> const T *
    {
        return &(current_pos.itself().get()->data()[index()]);
    }
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
            auto that = std::make_shared<node>(-1);
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
    Property<std::shared_ptr<node>> current_pos;

private:
    std::shared_ptr<Pager> pager;
};

template <class T, int16_t ORDER = 3>
class BPTree
{
    using node = Node<T, ORDER>;
    using iterator = Iterator<T, ORDER>;
    using nodeptr = std::shared_ptr<node>;
    enum class State
    {
        BT_OVERFLOW, // TODO:
        BT_UNDERFLOW,
        OK,
    };
    enum class InNode
    {
        LEFT,
        RIGHT,
    };
    struct Header
    {
        int64_t root_id = 1;
        int64_t count = 0;
    };

public:
    explicit BPTree(std::shared_ptr<Pager> pager)
    {
        this->pager = pager;
        if (pager->empty())
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
        while (!root->is_leaf())
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
        auto end = std::make_shared<node>(-1);
        iterator it(pager);
        it.current_pos = end;
        return it;
    }

    void insert(const T &value)
    {
        auto root = read_node(header->root_id);
        auto state = insert_helper(root, value);
        if (state == State::BT_OVERFLOW)
        {
            auto overflow = read_node(header->root_id);
            auto left_child = new_node();
            auto right_child = new_node();
            int64_t iter = 0;
            reset_children(overflow, left_child, InNode::LEFT, &iter);
            overflow->data.set(0, overflow->data()[iter]);
            left_child->right = right_child->page_id();
            if (!overflow->is_leaf())
            {
                iter++;
            }
            reset_children(overflow, right_child, InNode::RIGHT, &iter);
            overflow->count = 1;
            write_these_nodes(overflow, left_child, right_child, 0);
        }
    }

    void print()
    {
        print_count = 1;
        auto root = read_node(header->root_id);
        print_helper(root);
    }

private:
    int16_t print_count = 1;
    std::shared_ptr<Pager> pager;
    std::shared_ptr<Header> header = std::make_shared<Header>();

    void write_node(int64_t id, nodeptr n_ptr)
    {
        pager->save(id, n_ptr.get());
    }

    auto read_node(int64_t id) -> nodeptr
    {
        auto ret = std::make_shared<node>(-1);
        pager->recover(id, ret.get());
        return ret;
    }

    auto new_node() -> nodeptr
    {
        header->count++;
        auto ret = std::make_shared<node>(header->count);
        pager->save(0, header.get());
        return ret;
    }

    auto find_helper(const T &value, nodeptr root) -> iterator
    {
        auto pos = 0;
        if (!root->is_leaf())
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

    void print_helper(nodeptr ptr)
    {
        auto i = 0;
        for (i = 0; i < ptr->count(); i++)
        {
            if (ptr->children()[i])
            {
                auto child = read_node(ptr->children[i]);
                print_helper(child);
            }
            if (ptr->is_leaf())
            {
                if (print_count <= 64)
                {
                    auto num = fmt::format("[{}] ", print_count);
                    fmt::print(fg(fmt::terminal_color::bright_blue),
                               "{:>5}", num);
                    fmt::print("{}\n", ptr->data()[i].key);
                }
                else if (print_count == 65)
                {
                    fmt::print("...\n");
                    fmt::print("There is more than 64 records, ");
                    fmt::print("please use `find` command.\n");
                }
                else
                {
                    return;
                }
                print_count++;
            }
        }
        if (ptr->children()[i])
        {
            auto child = read_node(ptr->children()[i]);
            print_helper(child);
        }
    }

    auto insert_helper(nodeptr n, const T &value) -> State
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
            auto state = insert_helper(child, value);
            if (state == State::BT_OVERFLOW)
            {
                auto overflow = read_node(n->children()[pos]);
                auto left_child = overflow;
                left_child->count = 0;
                auto right_child = new_node();
                int64_t iter = 0;
                reset_children(overflow, left_child, InNode::LEFT, &iter);
                n->insert_InNode(pos, overflow->data()[iter]);
                if (!overflow->is_leaf())
                {
                    iter++;
                }
                else
                {
                    right_child->right = left_child->right();
                    left_child->right = right_child->page_id();
                    n->children.set(pos + 1, right_child->page_id());
                }
                reset_children(overflow, right_child, InNode::RIGHT, &iter);
                write_these_nodes(n, left_child, right_child, pos);
            }
        }
        else
        {
            n->insert_InNode(pos, value);
            write_node(n->page_id(), n);
        }
        return n->is_overflow() ? State::BT_OVERFLOW : State::OK;
    }

    void reset_children(nodeptr parent, nodeptr child, InNode p, int64_t *iter)
    {
        auto i = 0;
        auto flag = p == InNode::LEFT;
        for (i = 0; *iter < ceil(flag ? ORDER / 2.0 : ORDER + 1); i++)
        {
            child->children.set(i, parent->children()[*iter]);
            child->data.set(i, parent->data()[*iter]);
            child->count = child->count() + 1; // FIXME: incr()
            (*iter)++;
        }
        child->children.set(i, parent->children()[*iter]);
    }

    void write_these_nodes(nodeptr n1, nodeptr n2, nodeptr n3, int64_t pos)
    {
        n1->children.set(pos, n2->page_id());
        n1->children.set(pos + 1, n3->page_id());
        write_node(n1->page_id(), n1);
        write_node(n2->page_id(), n2);
        write_node(n3->page_id(), n3);
    }
};

#endif //SIMPLEDB_BPTREE_HPP_
