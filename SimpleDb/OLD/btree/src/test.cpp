#ifndef SIMPLEDB_BTREE_SRC_BTREE_HPP_
#define SIMPLEDB_BTREE_SRC_BTREE_HPP_

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include "./pagemanager.h"

using std::array;
using std::fill;
using std::function;
using std::shared_ptr;

template <class T>
class Property
{
protected:
    T value;

public:
    Property() {}
    explicit Property(const T &f) { value = f; }
    virtual ~Property() {}

    virtual auto operator=(const T &f) -> T & { return value = f; }
    virtual auto operator()() const -> const T & { return value; }
    virtual auto operator->() -> T * { return &value; }
    virtual void set(const T &f) { value = f; }
};

template <class T, int S>
class ArrayProperty
{
protected:
    array<T, S> value;

public:
    ArrayProperty() {}
    explicit ArrayProperty(const T &f) { value.fill(f); }
    explicit ArrayProperty(const array<T, S> &f) { value = f; }
    virtual ~ArrayProperty() {}

    virtual auto operator[](int i) -> T { return value[i]; }
    virtual auto operator()() const -> const array<T, S> & { return value; }
};

template <class T, int ORDER>
class Node
{
public:
    Property<int64_t> page_id{-1};
    Property<int64_t> count{0};
    Property<int64_t> right{0};
    ArrayProperty<T, ORDER> data =
        ArrayProperty<T, ORDER>(1);
    ArrayProperty<int64_t, ORDER> children =
        ArrayProperty<int64_t, ORDER>(0);

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
public:
    using node = Node<T, B>;
    Property<int64_t> index{0};
    Property<node> current_pos;
    std::shared_ptr<pagemanager> pm;

public:
    Iterator() {}
    explicit Iterator(std::shared_ptr<pagemanager> pm) : pm{pm} {}
    T operator*()
    {
        auto n = current_pos();
        return n.data[index];
    }
    Iterator &operator++()
    {
        if (index() < current_pos().count() - 1)
        {
            index = index() + 1;
        }
        else
        {
            index = 0;
            node that(-1);
            if (current_pos().right() == 0)
            {
                current_pos = that;
            }
            else
            {
                this->pm->recover(current_pos().right(), current_pos());
            }
        }
        return *this;
    }
    Iterator &operator=(const Iterator &that)
    {
        this->current_pos = that.current_pos();
        this->index = that.index;
        this->pm = that.pm;
        return *this;
    }
    Iterator(const Iterator &that)
    {
        this->current_pos = that.current_pos();
        this->index = that.index;
        this->pm = that.pm;
    }
    bool operator!=(const Iterator &that) const
    {
        if (this->current_pos().page_id() == that.current_pos().page_id())
        {
            return !(this->current_pos().data(index) ==
                     that.current_pos().data(that.index));
        }
        return true;
    }
};
int main()
{
    Iterator<int, 3> kk;
    Node<int, 3> b;
    b.count.set(233);
    ArrayProperty<int, 3> x;
    auto ddd = kk.current_pos().data();
    std::cout << b.count();
    ddd[2] = ddd[1] + 1;
    std::cout << ddd[2];
}

#endif //SIMPLEDB_BTREE_SRC_BTREE_HPP_
