// -*- C++ -*-
//===------------------------------ tree ------------------------------===//

#include <iostream>
#include <map>
#include <memory>
#include <list>
#include <set>
using namespace std;

#define USE_LIST_ITERATOR false
#define ADVANCED_ITERATOR false

#define RESET_COLOR "\e[0m"

#pragma region // tree node OK

template <class T>
class tree_node_
{
public:
    tree_node_();
    /*explicit*/ tree_node_(const T &data);

    tree_node_<T> *parent;
    tree_node_<T> *first_child;
    tree_node_<T> *last_child;
    tree_node_<T> *prev_sibling;
    tree_node_<T> *next_sibling;

    T data;
};

template <class T>
tree_node_<T>::tree_node_()
{
    this->parent = NULL;
    this->first_child = NULL;
    this->last_child = NULL;
    this->prev_sibling = NULL;
    this->next_sibling = NULL;
}

template <class T>
tree_node_<T>::tree_node_(const T &data)
{
    this->parent = NULL;
    this->first_child = NULL;
    this->last_child = NULL;
    this->prev_sibling = NULL;
    this->next_sibling = NULL;
    this->data = data;
}

#pragma endregion

#pragma region

template <class T, class Allocator = allocator<tree_node_<T>>>
class tree
{
public:
    typedef tree_node_<T> tree_node;
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

    class iterator_base;

    class pre_order_iterator;
    class in_order_iterator;
    class post_order_iterator;
    class level_order_iterator;

    class sibling_iterator;
    class leaf_iterator;

    class iterator_base_less
    {
    public:
        bool operator()(const typename tree<T, Allocator>::iterator_base &one,
                        const typename tree<T, Allocator>::iterator_base &two) const
        {
            return one.node < two.node;
        }
    };

    tree();
    /*explicit*/ tree(const value_type &val);
    /*explicit*/ tree(const iterator_base &base);
    tree(const tree<value_type, allocator_type> &other);
    ~tree();

    tree<value_type, allocator_type> &operator=(const tree<value_type, allocator_type> &); // FIXME:

    void print(pre_order_iterator it, pre_order_iterator end);
    void print();

    // 返回指向树的起始结点的迭代器, 默认先序.
    pre_order_iterator begin() const;
    // 返回指向树的终末结点的迭代器, 默认先序.
    pre_order_iterator end() const;
    // 返回指向树的起始结点的先序迭代器.
    pre_order_iterator pre_begin() const;
    // 返回指向树的终末结点的先序迭代器.
    pre_order_iterator pre_end() const;
    // 返回指向树的起始结点的中序迭代器. TODO:
    in_order_iterator in_begin() const;
    // 返回指向树的终末结点的中序迭代器. TODO:
    in_order_iterator in_end() const;
    // 返回指向树的起始结点的后序迭代器. TODO:
    post_order_iterator post_begin() const;
    // 返回指向树的终末结点的后序迭代器. TODO:
    post_order_iterator post_end() const;
    // 返回指向给定结点的起始子结点的兄弟迭代器.
    sibling_iterator begin(const iterator_base &pos) const;
    // 返回指向给定结点的终末子结点的兄弟迭代器.
    sibling_iterator end(const iterator_base &pos) const;

    // 返回指向给定结点的父结点的迭代器.
    template <class iterator_type>
    iterator_type parent(iterator_type pos);
    // 返回指向给定结点的前兄弟结点的迭代器.
    template <class iterator_type>
    iterator_type prev_sibling(iterator_type pos);
    // 返回指向给定结点的后兄弟结点的迭代器.
    template <class iterator_type>
    iterator_type next_sibling(iterator_type pos);

    // 清除树的所有结点.
    void clear();
    // 清除给定结点, 返回指向下个结点的迭代器.
    template <class iterator_type>
    iterator_type erase(iterator_type pos);
    // 清除给定结点的所有子结点.
    void erase_children(const iterator_base &pos);
    // 清除给定结点的所有右兄弟结点.
    void erase_right_siblings(const iterator_base &pos);
    // 清除给定结点的所有左兄弟结点.
    void erase_left_siblings(const iterator_base &pos);

    // 插入空结点为给定结点的终末子结点.
    template <class iterator_type>
    iterator_type append_child(iterator_type pos);
    // 插入空结点为给定结点的起始子结点.
    template <class iterator_type>
    iterator_type prepend_child(iterator_type pos);
    // 插入含值结点为给定结点的终末子结点.
    template <class iterator_type>
    iterator_type append_child(iterator_type pos, const value_type &val);
    // 插入含值结点为给定结点的起始子结点.
    template <class iterator_type>
    iterator_type prepend_child(iterator_type pos, const value_type &val);
    // 把 other 指向的结点 (包含子树) 插入为给定结点 pos 的终末子结点.
    template <class iterator_type>
    iterator_type append_child(iterator_type pos, iterator_type other);
    // 把 other 指向的结点 (包含子树) 插入为给定结点 pos 的起始子结点.
    template <class iterator_type>
    iterator_type prepend_child(iterator_type pos, iterator_type other);
    // 把给定区间 [begin, end] 内的结点 (包含它们的子树) 插入为给定结点 pos 的终末子结点.
    template <class iterator_type>
    iterator_type append_children(iterator_type pos, sibling_iterator begin, sibling_iterator end);
    // 把给定区间 [begin, end] 内的结点 (包含它们的子树) 插入为给定结点 pos 的起始子结点.
    template <class iterator_type>
    iterator_type prepend_children(iterator_type pos, sibling_iterator begin, sibling_iterator end);

    //
    pre_order_iterator set_head(const value_type &val);
    //
    template <class iterator_type>
    iterator_type insert(iterator_type pos, const value_type &val);
    //
    sibling_iterator insert(sibling_iterator pos, const value_type &val);
    //
    template <class iterator_type>
    iterator_type insert_subtree(iterator_type pos, const iterator_base &base);
    //
    template <class iterator_type>
    iterator_type insert_after(iterator_type pos, const value_type &val);
    //
    template <class iterator_type>
    iterator_type insert_subtree_after(iterator_type pos, const iterator_base &base);

    // 把给定结点替换为新结点.
    template <class iterator_type>
    iterator_type replace(iterator_type pos, const value_type &val);
    // 把给定结点 pos 替换为另一个结点 other (包含子树).
    template <class iterator_type>
    iterator_type replace(iterator_type pos, const iterator_base &other);
    // 把给定区间 [pos_begin, pos_end] 内的结点替换为另一个区间 [other_begin, other_end] 内的结点 (包含子树). TODO:
    sibling_iterator replace(sibling_iterator pos_begin, sibling_iterator pos_end,
                             sibling_iterator other_begin, sibling_iterator other_end);

    // 把给定结点的所有子结点移为其兄弟结点, 返回指向其本身的迭代器.
    template <class iterator_type>
    iterator_type flatten(iterator_type pos);
    // 把区间 [begin, end] 内所有结点移动为给定结点 pos 的子结点.
    template <class iterator_type>
    iterator_type re_parent(iterator_type pos, sibling_iterator begin, sibling_iterator end);
    // 把另一个结点 other 的子结点移动为给定结点 pos 的子结点.
    template <class iterator_type>
    iterator_type re_parent(iterator_type pos, iterator_type other);

    // 在给定结点和其父结点之间添加新结点.
    template <class iterator_type>
    iterator_type wrap(iterator_type pos, const value_type &val);

    // TODO:
    template <class iterator_type>
    iterator_type move_after(iterator_type to, iterator_type from);
    // TODO:
    template <class iterator_type>
    iterator_type move_before(iterator_type to, iterator_type from);
    // TODO:
    sibling_iterator move_before(sibling_iterator to, sibling_iterator from);
    // TODO:
    template <class iterator_type>
    iterator_type move_on_top(iterator_type to, iterator_type from);

    // TODO:
    tree move_out(pre_order_iterator);
    // TODO:
    template <class iterator_type>
    iterator_type move_in(iterator_type, tree &);
    // TODO:
    template <class iterator_type>
    iterator_type move_in_below(iterator_type, tree &);
    // TODO:
    template <class iterator_type>
    iterator_type move_in_as_nth_child(iterator_type, size_t, tree &);

    // 合并两棵树.
    void merge(sibling_iterator, sibling_iterator, sibling_iterator, sibling_iterator, bool duplicate_leaves = false);
    // 对区间 [begin, end] 的子树排序. TODO:
    void sort(sibling_iterator begin, sibling_iterator end, bool deep = false);
    // 对区间 [begin, end] 的子树排序, 使用自定义排序规则 cmp. TODO:
    template <class StrictWeakOrdering>
    void sort(sibling_iterator begin, sibling_iterator end, StrictWeakOrdering cmp, bool deep = false);
    // WHY? TODO:
    template <class iterator_type>
    bool equal(const iterator_type &one, const iterator_type &two, const iterator_type &three) const;
    // WHY? TODO:
    template <class iterator_type, class BinaryPredicate>
    bool equal(const iterator_type &one, const iterator_type &two, const iterator_type &three, BinaryPredicate) const;
    // 检查两个结点的子树是否相等. TODO:
    template <class iterator_type>
    bool equal_subtree(const iterator_type &, const iterator_type &) const;
    // 检查两个结点的子树是否相等. TODO:
    template <class iterator_type, class BinaryPredicate>
    bool equal_subtree(const iterator_type &, const iterator_type &to, BinaryPredicate) const;
    // 获得由区间 [begin, end] 内结点组成的一棵子树.
    tree subtree(sibling_iterator begin, sibling_iterator end) const;
    // 交换给定结点和其兄弟结点 (包含子树).
    void swap(sibling_iterator it);
    // 交换两个结点 (包含子树).
    void swap(pre_order_iterator, pre_order_iterator);

    // 返回总结点个数.
    int size() const;
    // 返回以给定结点为根的子树的总结点个数.
    int size(const iterator_base &) const;
    // 检查树是否为空.
    bool empty() const;
    // 获得给定结点 pos 到根的深度.
    static int depth(const iterator_base &pos);
    // 获得给定结点 pos 到另一个结点 other 的深度.
    static int depth(const iterator_base &pos, const iterator_base &other);
    // 获得一棵树的最大深度.
    int max_depth() const;
    // 获得以给定结点为根的树的最大深度.
    int max_depth(const iterator_base &pos) const;
    // 获得给定结点的子结点个数.
    int children_count(const iterator_base &pos);
    // 获得给定结点的兄弟结点个数.
    int siblings_count(const iterator_base &pos) const;
    // 判断给定结点 pos 是否在区间 [begin, end] (包含子树) 内.
    bool is_in_subtree(const iterator_base &pos, const iterator_base &begin, const iterator_base &end) const;
    // 检查给定结点是否有效.
    bool is_valid(const iterator_base &pos) const;
    // 获得给定两结点的最近共同祖先.
    pre_order_iterator lowest_common_ancestor(const iterator_base &pos1, const iterator_base &pos2) const;

    // 获得给定结点在其所有兄弟结点中的序号.
    int index(sibling_iterator pos) const;
    // 获得给定结点 pos 的序号为 n 的子结点.
    sibling_iterator child(const iterator_base &pos, int n);
    // 获得给定结点 pos 的序号为 n 的兄弟结点.
    sibling_iterator sibling(const iterator_base &pos, int n);

    tree_node *head;
    tree_node *feet;
    allocator_type alloc;

    void initialize();
    void copy(const tree &other);
};

#pragma endregion

#pragma region // Iterator Base

template <class value_type, class allocator_type>
class tree<value_type, allocator_type>::iterator_base
{
public:
    iterator_base();
    /*explicit*/ iterator_base(tree_node *);

    value_type &operator*() const;
    value_type *operator->() const;

    void skip_children();
    void skip_children(bool);
    int children_count() const;

    sibling_iterator begin() const;
    sibling_iterator end() const;
    tree_node *node;

protected:
    bool skip;
};

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::iterator_base::iterator_base()
{
    this->node = NULL;
    this->skip = false;
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::iterator_base::iterator_base(tree_node *node)
{
    this->node = node;
    this->skip = false;
}

template <class value_type, class allocator_type>
value_type &tree<value_type, allocator_type>::iterator_base::operator*() const
{
    return node->data;
}

template <class value_type, class allocator_type>
value_type *tree<value_type, allocator_type>::iterator_base::operator->() const
{
    return &(node->data);
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::iterator_base::skip_children()
{
    skip = true;
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::iterator_base::skip_children(bool outside_flag)
{
    skip = outside_flag;
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::iterator_base::children_count() const
{
    tree_node *pos = node->first_child;
    int cnt = 0;
    while (pos != NULL)
    {
        pos = pos->next_sibing;
        cnt++;
    }
    return cnt;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::iterator_base::begin() const
{
    if (node->first_child == 0)
        return end();

    sibling_iterator ret(node->first_child);
    ret.parent = this->node;
    return ret;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::iterator_base::end() const
{
    sibling_iterator ret(0);
    ret.parent = node;
    return ret;
}

#pragma endregion

#pragma region // Pre-order Iterator

template <class value_type, class allocator_type>
class tree<value_type, allocator_type>::pre_order_iterator : public tree<value_type, allocator_type>::iterator_base
{
public:
    pre_order_iterator();
    /*explicit*/ pre_order_iterator(tree_node *node);
    /*explicit*/ pre_order_iterator(const iterator_base &base);
    /*explicit*/ pre_order_iterator(const sibling_iterator &sib);

    bool operator==(const pre_order_iterator &other) const;
    bool operator!=(const pre_order_iterator &other) const;
    bool is_last()
    {
        return this->node->next_sibling == NULL;
    }
    bool is_q()
    {
        return this->node->first_child == NULL;
    }

    pre_order_iterator &operator++();
    pre_order_iterator &operator--();
    const pre_order_iterator operator++(int);
    const pre_order_iterator operator--(int);
    pre_order_iterator &operator+=(int increment);
    pre_order_iterator &operator-=(int decrement);

    pre_order_iterator &next_skip_children();
};

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::pre_order_iterator::pre_order_iterator() : iterator_base()
{
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::pre_order_iterator::pre_order_iterator(tree_node *node) : iterator_base(node)
{
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::pre_order_iterator::pre_order_iterator(const iterator_base &base) : iterator_base(base.node)
{
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::pre_order_iterator::pre_order_iterator(const sibling_iterator &sib) : iterator_base(sib.node)
{
    // WHY?
    if (this->node == NULL)
    {
        if (sib.last() != NULL)
        {
            this->node = sib.last();
        }
        else
        {
            this->node = sib.parent;
        }
        this->skip_children();
        (*this)++;
    }
}

template <class value_type, class allocator_type>
bool tree<value_type, allocator_type>::pre_order_iterator::operator==(const pre_order_iterator &other) const
{
    return other.node == this->node;
}

template <class value_type, class allocator_type>
bool tree<value_type, allocator_type>::pre_order_iterator::operator!=(const pre_order_iterator &other) const
{
    return other.node != this->node;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator &tree<value_type, allocator_type>::pre_order_iterator::operator++()
{
    assert(this->node != NULL);
    if (this->skip == false && this->node->first_child != NULL)
    {
        this->node = this->node->first_child;
    }
    else
    {
        this->skip = false;
        while (this->node->next_sibling == NULL)
        {
            this->node = this->node->parent;
            if (this->node == NULL)
            {
                return *this;
            }
        }
        this->node = this->node->next_sibling;
    }
    return *this;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator &tree<value_type, allocator_type>::pre_order_iterator::operator--()
{
    assert(this->node != NULL);
    if (this->node->prev_sibling)
    {
        this->node = this->node->prev_sibling;
        while (this->node->last_child)
        {
            this->node = this->node->last_child;
        }
    }
    else
    {
        this->node = this->node->parent;
        if (this->node == NULL)
        {
            return *this;
        }
    }
    return *this;
}

template <class value_type, class allocator_type>
const typename tree<value_type, allocator_type>::pre_order_iterator tree<value_type, allocator_type>::pre_order_iterator::operator++(int)
{
    pre_order_iterator copy = *this;
    ++(*this);
    return copy;
}

template <class value_type, class allocator_type>
const typename tree<value_type, allocator_type>::pre_order_iterator tree<value_type, allocator_type>::pre_order_iterator::operator--(int)
{
    pre_order_iterator copy = *this;
    --(*this);
    return copy;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator &tree<value_type, allocator_type>::pre_order_iterator::operator+=(int increment)
{
    while (increment > 0)
    {
        (*this)++;
        increment--;
    }
    return *this;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator &tree<value_type, allocator_type>::pre_order_iterator::operator-=(int decrement)
{
    while (decrement > 0)
    {
        (*this)--;
        decrement--;
    }
    return *this;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator &tree<value_type, allocator_type>::pre_order_iterator::next_skip_children()
{
    (*this).skip_children();
    (*this)++;
    return *this;
}

#pragma endregion

#pragma region // Sibling Iterator

template <class value_type, class allocator_type>
class tree<value_type, allocator_type>::sibling_iterator : public tree<value_type, allocator_type>::iterator_base
{
public:
    sibling_iterator();
    /*explicit*/ sibling_iterator(tree_node *node);
    /*explicit*/ sibling_iterator(const iterator_base &base);
    sibling_iterator(const sibling_iterator &sib);

    bool operator==(const sibling_iterator &other) const;
    bool operator!=(const sibling_iterator &other) const;

    sibling_iterator &operator++();
    sibling_iterator &operator--();
    const sibling_iterator operator++(int);
    const sibling_iterator operator--(int);
    sibling_iterator &operator+=(int increment);
    sibling_iterator &operator-=(int decrement);

    tree_node *first() const;
    tree_node *last() const;

    void set_parent();
    tree_node *parent;
};

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::sibling_iterator::sibling_iterator() : iterator_base()
{
    set_parent();
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::sibling_iterator::sibling_iterator(tree_node *node) : iterator_base(node)
{
    set_parent();
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::sibling_iterator::sibling_iterator(const iterator_base &base) : iterator_base(base.node)
{
    set_parent();
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::sibling_iterator::sibling_iterator(const sibling_iterator &sib) : iterator_base(sib)
{
    this->parent = sib.parent;
}

template <class value_type, class allocator_type>
bool tree<value_type, allocator_type>::sibling_iterator::operator==(const sibling_iterator &other) const
{
    return other.node == this->node;
}

template <class value_type, class allocator_type>
bool tree<value_type, allocator_type>::sibling_iterator::operator!=(const sibling_iterator &other) const
{
    return other.node != this->node;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator &tree<value_type, allocator_type>::sibling_iterator::operator++()
{
    if (this->node != NULL)
    {
        this->node = this->node->next_sibling;
    }
    return *this;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator &tree<value_type, allocator_type>::sibling_iterator::operator--()
{
    if (this->node != NULL)
    {
        this->node = this->node->prev_sibling;
    }
    else
    {
        assert(parent != NULL);
        this->node = parent->last_child;
    }
    return *this;
}

template <class value_type, class allocator_type>
const typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::sibling_iterator::operator++(int)
{
    sibling_iterator copy = *this;
    ++(*this);
    return copy;
}

template <class value_type, class allocator_type>
const typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::sibling_iterator::operator--(int)
{
    sibling_iterator copy = *this;
    --(*this);
    return copy;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator &tree<value_type, allocator_type>::sibling_iterator::operator+=(int increment)
{
    while (increment > 0)
    {
        (*this)++;
        increment--;
    }
    return *this;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator &tree<value_type, allocator_type>::sibling_iterator::operator-=(int decrement)
{
    while (decrement > 0)
    {
        (*this)--;
        decrement--;
    }
    return *this;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::tree_node *tree<value_type, allocator_type>::sibling_iterator::first() const
{
    return parent->first_child;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::tree_node *tree<value_type, allocator_type>::sibling_iterator::last() const
{
    return parent->last_child;
}

template <class value_type, class tree_node_allocator>
void tree<value_type, tree_node_allocator>::sibling_iterator::set_parent()
{
    parent = NULL;
    if (this->node->parent != NULL)
    {
        parent = this->node->parent;
    }
}

#pragma endregion

#pragma region // ...

template <class value_type, class allocator_type>
class tree<value_type, allocator_type>::post_order_iterator : public tree<value_type, allocator_type>::iterator_base
{
};

template <class value_type, class allocator_type>
class tree<value_type, allocator_type>::level_order_iterator : public tree<value_type, allocator_type>::iterator_base
{
};

template <class value_type, class allocator_type>
class tree<value_type, allocator_type>::leaf_iterator : public tree<value_type, allocator_type>::iterator_base
{
};

#pragma endregion

#pragma region // tree functions implementation

//

//

//

//

//

//

//

//

//

//

//

//

//

//

//
template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::print(pre_order_iterator begin, pre_order_iterator end)
{
    const string &COLOR = "\033[0m";
    const string &RESET = "\033[0m";
    cout << "════════════════════════════════════════════════\n";
    if (!is_valid(begin))
    {
        return;
    }
    int root_depth = depth(begin);
    int over_depth = 0;
    std::list<int> overs;
    cout << "┯ ";
    pre_order_iterator it = begin;
    while (it != end)
    {
        pre_order_iterator current_it = it++;
        bool flag = current_it.is_last();
        int current_depth = depth(current_it);
        int next_depth = depth(it);
        if (flag && current_depth < next_depth)
        {
            over_depth = current_depth;
            overs.push_back(over_depth);
        }
        for (int i = 1 + root_depth; i < current_depth; i++)
        {
            cout << COLOR << (find(overs.begin(), overs.end(), i) == overs.end() ? "│ " : "  ") << RESET;
        }
        if (current_depth > next_depth)
        {
            over_depth = -1;
            if (!overs.empty() && *max_element(overs.begin(), overs.end()) > next_depth)
            {
                overs.clear();
            }
        }
        if (current_depth != root_depth)
        {
            cout << COLOR;
            cout << (flag ? "└─" : "├─");
            cout << (current_it.is_q() == 0 ? "┯" : "━");
            cout << (" ");
            cout << RESET;
        }
        cout << (*current_it);
        if (children_count(current_it) != 0)
        {
            cout << COLOR << "(" << children_count(current_it) << ")" << RESET;
        }
        cout << endl;
    }
    cout << "════════════════════════════════════════════════\n";
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::print()
{
    print(begin(), end());
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::initialize()
{
    head = alloc.allocate(1, NULL);
    feet = alloc.allocate(1, NULL);
    alloc.construct(head, tree_node());
    alloc.construct(feet, tree_node());

    head->parent = NULL;
    head->first_child = NULL;
    head->last_child = NULL;
    head->prev_sibling = NULL;
    head->next_sibling = feet;

    feet->parent = NULL;
    feet->first_child = NULL;
    feet->last_child = NULL;
    feet->prev_sibling = head;
    feet->next_sibling = NULL;
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::copy(const tree<value_type, allocator_type> &other)
{
    clear();
    pre_order_iterator it = other.begin(), to = begin();
    while (it != other.end())
    {
        to = insert(to, (*it));
        it.skip_children();
        ++it;
    }
    to = begin();
    it = other.begin();
    while (it != other.end())
    {
        to = replace(to, it);
        to.skip_children();
        it.skip_children();
        ++to;
        ++it;
    }
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::tree()
{
    initialize();
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::tree(const value_type &val)
{
    initialize();
    set_head(val);
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::tree(const iterator_base &base)
{
    initialize();
    set_head(*base);
    replace(begin(), base);
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::tree(const tree<value_type, allocator_type> &other)
{
    initialize();
    copy(other);
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type>::~tree()
{
    clear();
    alloc.destroy(head);
    alloc.destroy(feet);
    alloc.deallocate(head, 1);
    alloc.deallocate(feet, 1);
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type> &tree<value_type, allocator_type>::operator=(const tree<value_type, allocator_type> &other)
{
    if (this != &other)
    {
        // FIXME: copy_(other);
    }
    return *this;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator tree<value_type, allocator_type>::begin() const
{
    // WHY?
    return pre_order_iterator(head->next_sibling);
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator tree<value_type, allocator_type>::end() const
{
    return pre_order_iterator(feet);
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator tree<value_type, allocator_type>::pre_begin() const
{
    return begin();
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator tree<value_type, allocator_type>::pre_end() const
{
    return end();
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::in_order_iterator tree<value_type, allocator_type>::in_begin() const
{
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::in_order_iterator tree<value_type, allocator_type>::in_end() const
{
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::post_order_iterator tree<value_type, allocator_type>::post_begin() const
{
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::post_order_iterator tree<value_type, allocator_type>::post_end() const
{
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::begin(const iterator_base &pos) const
{
    assert(pos.node != NULL);
    if (pos.node->first_child == NULL)
    {
        return end(pos);
    }
    return pos.node->first_child;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::end(const iterator_base &pos) const
{
    // WHY?
    sibling_iterator sib;
    sib.parent = pos.node;
    return sib;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::parent(iterator_type pos)
{
    assert(pos.node != NULL);
    return iterator_type(pos.node->parent);
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::prev_sibling(iterator_type pos)
{
    assert(pos.node != NULL);
    iterator_type t(pos);
    t.node = pos.node->prev_sibling;
    return t;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::next_sibling(iterator_type pos)
{
    assert(pos.node != NULL);
    iterator_type t(pos);
    t.node = pos.node->next_sibling;
    return t;
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::clear()
{
    if (head != NULL)
    {
        while (head->next_sibling != feet)
        {
            erase(pre_order_iterator(head->next_sibling));
        }
    }
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::erase(iterator_type pos)
{
    // WHY?
    tree_node *current = pos.node;
    assert(current != head);
    iterator_type t = pos;
    t.skip_children();
    t++;
    erase_children(pos);
    if (current->prev_sibling == NULL)
    {
        current->parent->first_child = current->next_sibling;
    }
    else
    {
        current->prev_sibling->next_sibling = current->next_sibling;
    }
    if (current->next_sibling == NULL)
    {
        current->parent->last_child = current->prev_sibling;
    }
    else
    {
        current->next_sibling->prev_sibling = current->prev_sibling;
    }

    alloc.destroy(current);
    alloc.deallocate(current, 1);
    return t;
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::erase_children(const iterator_base &base)
{
    // WHY?
    if (base.node == NULL)
    {
        return;
    }
    tree_node *current = base.node->first_child;
    tree_node *prev = NULL;
    while (current != NULL)
    {
        prev = current;
        current = current->next_sibling;
        erase_children(pre_order_iterator(prev));
        alloc.destroy(prev);
        alloc.deallocate(prev, 1);
    }
    base.node->first_child = NULL;
    base.node->last_child = NULL;
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::erase_right_siblings(const iterator_base &pos)
{
    // WHY?
    if (pos.node == NULL)
    {
        return;
    }
    tree_node *current = pos.node->next_sibling;
    tree_node *prev = NULL;
    while (current != NULL)
    {
        prev = current;
        current = current->next_sibling;
        erase_children(pre_order_iterator(prev));
        alloc.destroy(prev);
        alloc.deallocate(prev, 1);
    }
    pos.node->next_sibling = NULL;
    if (pos.node->parent != NULL)
    {
        pos.node->parent->last_child = pos.node;
    }
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::erase_left_siblings(const iterator_base &pos)
{
    // WHY?
    if (pos.node == NULL)
    {
        return;
    }
    tree_node *current = pos.node->prev_sibling;
    tree_node *prev = NULL;
    while (current != NULL)
    {
        prev = current;
        current = current->prev_sibling;
        erase_children(pre_order_iterator(prev));
        alloc.destroy(prev);
        alloc.deallocate(prev, 1);
    }
    pos.node->prev_sibling = NULL;
    if (pos.node->parent != NULL)
    {
        pos.node->parent->first_child = pos.node;
    }
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::append_child(iterator_type pos)
{
    assert(pos.node != head && pos.node != feet && pos.node != NULL);
    tree_node *n = alloc.allocate(1, NULL);
    alloc.construct(n, tree_node());
    n->first_child = NULL;
    n->last_child = NULL;
    n->parent = pos.node;
    if (pos.node->last_child != NULL)
    {
        pos.node->last_child->next_sibling = n;
    }
    else
    {
        pos.node->first_child = n;
    }
    n->prev_sibling = pos.node->last_child;
    pos.node->last_child = n;
    n->next_sibling = NULL;
    return n;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::prepend_child(iterator_type pos)
{
    assert(pos.node != head && pos.node != feet && pos.node != NULL);
    tree_node *n = alloc.allocate(1, NULL);
    alloc.construct(n, tree_node());
    n->first_child = NULL;
    n->last_child = NULL;
    n->parent = pos.node;
    if (pos.node->first_child != NULL)
    {
        pos.node->first_child->prev_sibling = n;
    }
    else
    {
        pos.node->last_child = n;
    }
    n->next_sibling = pos.node->first_child;
    pos.node->first_child = n;
    n->prev_sibling = NULL;
    return n;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::append_child(iterator_type pos, const value_type &val)
{
    assert(pos.node != head && pos.node != feet && pos.node != NULL);
    tree_node *n = alloc.allocate(1, NULL);
    alloc.construct(n, tree_node(val));
    n->first_child = NULL;
    n->last_child = NULL;
    n->parent = pos.node;
    if (pos.node->last_child != NULL)
    {
        pos.node->last_child->next_sibling = n;
    }
    else
    {
        pos.node->first_child = n;
    }
    n->prev_sibling = pos.node->last_child;
    pos.node->last_child = n;
    n->next_sibling = NULL;
    return n;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::prepend_child(iterator_type pos, const value_type &val)
{
    assert(pos.node != head && pos.node != feet && pos.node != NULL);
    tree_node *n = alloc.allocate(1, NULL);
    alloc.construct(n, tree_node(val));
    n->first_child = NULL;
    n->last_child = NULL;
    n->parent = pos.node;
    if (pos.node->first_child != NULL)
    {
        pos.node->first_child->prev_sibling = n;
    }
    else
    {
        pos.node->last_child = n;
    }
    n->next_sibling = pos.node->first_child;
    pos.node->first_child = n;
    n->prev_sibling = NULL;
    return n;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::append_child(iterator_type pos, iterator_type other)
{
    assert(pos.node != head && pos.node != feet && pos.node != NULL);
    sibling_iterator sib = append_child(pos, value_type());
    return replace(sib, other);
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::prepend_child(iterator_type pos, iterator_type other)
{
    assert(pos.node != head && pos.node != feet && pos.node != NULL);
    sibling_iterator sib = prepend_child(pos, value_type());
    return replace(sib, other);
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::append_children(iterator_type pos, sibling_iterator begin, sibling_iterator end)
{
    assert(pos.node != head && pos.node != feet && pos.node != NULL);
    iterator_type t = begin;
    while (begin != end)
    {
        insert_subtree(pos.end(), begin);
        begin++;
    }
    return t;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::prepend_children(iterator_type pos, sibling_iterator begin, sibling_iterator end)
{
    assert(pos.node != head && pos.node != feet && pos.node != NULL);
    iterator_type t = begin;
    while (begin != end)
    {
        insert_subtree(pos.begin(), begin);
        begin++;
    }
    return t;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator tree<value_type, allocator_type>::set_head(const value_type &val)
{
    assert(head->next_sibling == feet);
    return insert(pre_order_iterator(feet), val);
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::insert(iterator_type pos, const value_type &val)
{
    if (pos.node == NULL)
    {
        pos.node = feet;
    }
    assert(pos.node != head);

    tree_node *t = alloc.allocate(1, NULL);
    alloc.construct(t, val);

    t->first_child = NULL;
    t->last_child = NULL;

    //WHY?
    t->parent = pos.node->parent;
    t->next_sibling = pos.node;
    t->prev_sibling = pos.node->prev_sibling;
    pos.node->prev_sibling = t;

    if (t->prev_sibling == NULL)
    {
        if (t->parent != NULL)
        {
            t->parent->first_child = t;
        }
    }
    else
    {
        t->prev_sibling->next_sibling = t;
    }
    return t;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::insert(sibling_iterator pos, const value_type &val)
{
    // WHY?
    tree_node *t = alloc.allocate(1, NULL);
    alloc.construct(t, val);
    t->first_child = NULL;
    t->last_child = NULL;
    t->next_sibling = pos.node;
    if (pos.node == NULL)
    {
        t->parent = pos.parent;
        t->prev_sibling = pos.last();
        t->parent->last_child = t;
    }
    else
    {
        t->parent = pos.node->parent;
        t->prev_sibling = pos.node->prev_sibling;
        pos.node->prev_sibling = t;
    }

    if (t->prev_sibling == NULL)
    {
        if (t->parent)
        {
            t->parent->first_child = t;
        }
    }
    else
    {
        t->prev_sibling->next_sibling = t;
    }
    return t;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::insert_subtree(iterator_type pos, const iterator_base &base)
{
    // WHY?
    iterator_type it = insert(pos, value_type());
    return replace(it, base);
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::insert_after(iterator_type pos, const value_type &val)
{
    tree_node *t = alloc.allocate(1, NULL);
    alloc.construct(t, val);
    t->first_child = NULL;
    t->last_child = NULL;
    t->parent = pos.node->parent;
    t->prev_sibling = pos.node;
    t->next_sibling = pos.node->next_sibling;
    pos.node->next_sibling = t;

    if (t->next_sibling == NULL)
    {
        if (t->parent)
        {
            t->parent->last_child = t;
        }
    }
    else
    {
        t->next_sibling->prev_sibling = t;
    }
    return t;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::insert_subtree_after(iterator_type pos, const iterator_base &base)
{
    iterator_type it = insert_after(pos, value_type());
    return replace(it, base);
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::replace(iterator_type pos, const value_type &val)
{
    pos.node->data = val;
    return pos;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::replace(iterator_type pos, const iterator_base &other)
{
    // WHY?

    assert(pos.node != head);
    tree_node *current_from = other.node;
    tree_node *start_from = other.node;
    tree_node *current_to = pos.node;

    erase_children(pos);
    tree_node *n = alloc.allocate(1, NULL);
    alloc.construct(n, (*other));

    n->first_child = NULL;
    n->last_child = NULL;
    if (current_to->prev_sibling == NULL)
    {
        if (current_to->parent != NULL)
        {
            current_to->parent->first_child = n;
        }
    }
    else
    {
        current_to->prev_sibling->next_sibling = n;
    }
    n->prev_sibling = current_to->prev_sibling;
    if (current_to->next_sibling == NULL)
    {
        if (current_to->parent != NULL)
        {
            current_to->parent->last_child = n;
        }
    }
    else
    {
        current_to->next_sibling->prev_sibling = n;
    }
    n->next_sibling = current_to->next_sibling;
    n->parent = current_to->parent;
    alloc.destroy(current_to);
    alloc.deallocate(current_to, 1);
    current_to = n;

    tree_node *last = other.node->next_sibling;

    pre_order_iterator to = n;
    do
    {
        assert(current_from != NULL);
        if (current_from->first_child != NULL)
        {
            current_from = current_from->first_child;
            to = append_child(to, current_from->data);
        }
        else
        {
            while (current_from->next_sibling == NULL && current_from != start_from)
            {
                current_from = current_from->parent;
                to = parent(to);
                assert(current_from != NULL);
            }
            current_from = current_from->next_sibling;
            if (current_from != last)
            {
                to = append_child(parent(to), current_from->data);
            }
        }
    } while (current_from != last);

    return current_to;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::replace(
    sibling_iterator pos_begin, sibling_iterator pos_end,
    sibling_iterator other_begin, sibling_iterator other_end)
{
    // FIXME:
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::flatten(iterator_type pos)
{
    if (pos.node->first_child == NULL)
    {
        return pos;
    }
    tree_node *t = pos.node->first_child;
    while (t != NULL)
    {
        t->parent = pos.node->parent;
        t = t->next_sibling;
    }
    if (pos.node->next_sibling != NULL)
    {
        pos.node->last_child->next_sibling = pos.node->next_sibling;
        pos.node->next_sibling->prev_sibling = pos.node->last_child;
    }
    else
    {
        pos.node->parent->last_child = pos.node->last_child;
    }
    pos.node->next_sibling = pos.node->first_child;
    pos.node->next_sibling->prev_sibling = pos.node;
    pos.node->first_child = NULL;
    pos.node->last_child = NULL;
    return pos;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::re_parent(iterator_type pos, sibling_iterator begin, sibling_iterator end)
{
    tree_node *first = begin.node;
    tree_node *last = first;

    assert(first != pos.node);

    if (begin == end)
    {
        return begin;
    }
    while (begin != end)
    {
        last = last->next_sibling;
        begin++;
    }
    // XXX:
    first->prev_sibling == NULL ? first->parent->first_child = last->next_sibling
                                : first->prev_sibling->next_sibling = last->next_sibling;
    last->next_sibling == NULL ? last->parent->last_child = first->prev_sibling
                               : last->next_sibling->prev_sibling = first->prev_sibling;
    if (pos.node->first_child == NULL)
    {
        pos.node->first_child = first;
        pos.node->last_child = last;
        first->prev_sibling = NULL;
        last->next_sibling = NULL;
    }
    else
    {
        pos.node->last_child->next_sibling = first;
        pos.node->last_child = last;
        first->prev_sibling = pos.node->last_child;
        last->next_sibling = NULL;
    }
    for (tree_node *f = first; f != last; f = f->next_sibling)
    {
        f->parent = pos.node;
    }
    return first;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::re_parent(iterator_type pos, iterator_type from)
{
    if (from.node->first_child == NULL)
    {
        return pos;
    }
    return re_parent(pos, from.node->first_child, end(from));
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::wrap(iterator_type pos, const value_type &val)
{
    // WHY?
    assert(pos.node != NULL);
    sibling_iterator from = pos;
    sibling_iterator to = pos;
    to++;
    iterator_type t = insert(pos, val);
    re_parent(t, from, to);
    return t;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::move_after(iterator_type to, iterator_type from)
{
    // WHY?
    tree_node *node_to = to.node;
    tree_node *node_from = from.node;
    if (node_to == node_from || (node_to->next_sibling != NULL && node_to->next_sibling == node_from))
    {
        return from;
    }
    (node_from->prev_sibling != NULL ? node_from->prev_sibling->next_sibling
                                     : node_from->parent->first_child) = node_from->next_sibling;
    (node_from->next_sibling != NULL ? node_from->next_sibling->prev_sibling
                                     : node_from->parent->last_child) = node_from->prev_sibling;
    (node_to->next_sibling != NULL ? node_to->next_sibling->prev_sibling
                                   : node_to->parent->last_child) = node_from;
    node_from->next_sibling = node_to->next_sibling;
    node_to->next_sibling = node_from;
    node_from->prev_sibling = node_to;
    node_from->parent = node_to->parent;
    return node_from;
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::move_before(iterator_type to, iterator_type from)
{
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::move_before(sibling_iterator to, sibling_iterator from)
{
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::move_on_top(iterator_type to, iterator_type from)
{
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type> tree<value_type, allocator_type>::move_out(pre_order_iterator)
{
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::move_in(iterator_type, tree &)
{
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::move_in_below(iterator_type, tree &)
{
}

template <class value_type, class allocator_type>
template <class iterator_type>
iterator_type tree<value_type, allocator_type>::move_in_as_nth_child(iterator_type, size_t, tree &)
{
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::merge(sibling_iterator to1, sibling_iterator to2,
                                             sibling_iterator from1, sibling_iterator from2,
                                             bool duplicate_leaves)
{
    // WHY?
    sibling_iterator fnd;
    while (from1 != from2)
    {
        fnd = std::find(to1, to2, *from1);
        if (fnd != to2)
        {
            if (from1.begin() == from1.end())
            {
                if (duplicate_leaves)
                {
                    append_child(parent(to1), *from1);
                }
            }
            else
            {
                merge(fnd.begin(), fnd.end(), from1.begin(), from1.end(), duplicate_leaves);
            }
        }
        else
        {
            insert_subtree(to2, from1);
        }
        from1++;
    }
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::sort(sibling_iterator, sibling_iterator, bool deep)
{
}

template <class value_type, class allocator_type>
template <class StrictWeakOrdering>
void tree<value_type, allocator_type>::sort(sibling_iterator A, sibling_iterator B, StrictWeakOrdering cmp, bool deep)
{
}

template <class value_type, class allocator_type>
template <class iterator_type>
bool tree<value_type, allocator_type>::equal(const iterator_type &one, const iterator_type &two, const iterator_type &three) const
{
}

template <class value_type, class allocator_type>
template <class iterator_type, class BinaryPredicate>
bool tree<value_type, allocator_type>::equal(const iterator_type &one, const iterator_type &two, const iterator_type &three, BinaryPredicate) const
{
}

template <class value_type, class allocator_type>
template <class iterator_type>
bool tree<value_type, allocator_type>::equal_subtree(const iterator_type &, const iterator_type &) const
{
}

template <class value_type, class allocator_type>
template <class iterator_type, class BinaryPredicate>
bool tree<value_type, allocator_type>::equal_subtree(const iterator_type &, const iterator_type &to, BinaryPredicate) const
{
}

template <class value_type, class allocator_type>
tree<value_type, allocator_type> tree<value_type, allocator_type>::subtree(sibling_iterator from, sibling_iterator to) const
{
    assert(from != to);
    tree t;
    t.set_head(value_type());
    t.replace(t.begin(), t.end(), from, to);
    return t;
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::swap(sibling_iterator sib)
{
    tree_node *next = sib.node->next_sibling;
    if (next != NULL)
    {
        sib.node->prev_sibling != NULL ? sib.node->prev_sibling->next_sibling = next
                                       : sib.node->parent->first_child = next;
        next->prev_sibling = sib.node->prev_sibling;
        tree_node *nextnext = next->next_sibling;
        nextnext != NULL ? nextnext->prev_sibling = sib.node
                         : sib.node->parent->last_child = sib.node;
        next->next_sibling = sib.node;
        sib.node->prev_sibling = next;
        sib.node->next_sibling = nextnext;
    }
}

template <class value_type, class allocator_type>
void tree<value_type, allocator_type>::swap(pre_order_iterator this_it, pre_order_iterator that_it)
{
    if (this_it.node->next_sibling == that_it.node)
    {
        swap(this_it);
    }
    else if (that_it.node->next_sibling == this_it.node)
    {
        swap(that_it);
    }
    else
    {
        tree_node *this_next = this_it.node->next_sibling;
        tree_node *that_next = that_it.node->next_sibling;
        tree_node *this_prev = this_it.node->prev_sibling;
        tree_node *that_prev = that_it.node->prev_sibling;
        tree_node *this_parent = this_it.node->parent;
        tree_node *that_parent = that_it.node->parent;

        this_it.node->parent = that_parent;
        this_it.node->next_sibling = that_next;

        that_next != NULL ? that_next->prev_sibling = this_it.node
                          : that_parent->last_child = this_it.node;
        this_it.node->prev_sibling = that_prev;
        that_prev != NULL ? that_prev->next_sibling = this_it.node
                          : that_parent->first_child = this_it.node;

        that_it.node->parent = this_parent;
        that_it.node->next_sibling = this_next;
        this_next != NULL ? this_next->prev_sibling = that_it.node
                          : this_parent->last_child = that_it.node;
        that_it.node->prev_sibling = this_prev;
        this_prev != NULL ? this_prev->next_sibling = that_it.node
                          : this_parent->first_child = that_it.node;
    }
    // WHY?
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::size() const
{
    int cnt = 0;
    pre_order_iterator it = begin();
    pre_order_iterator eit = end();
    while (it != eit)
    {
        cnt++;
        it++;
    }
    return cnt;
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::size(const iterator_base &base) const
{
    int cnt = 0;
    pre_order_iterator it = base;
    pre_order_iterator eit = base;
    eit.skip_children(); // WHY?
    eit++;
    while (it != eit)
    {
        cnt++;
        it++;
    }
    return cnt;
}

template <class value_type, class allocator_type>
bool tree<value_type, allocator_type>::empty() const
{
    // WHY?
    //pre_order_iterator it = begin(), eit = end();
    //return (it == eit);
    return begin() == end();
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::depth(const iterator_base &base)
{
    tree_node *pos = base.node;
    assert(pos != NULL);
    int cnt = 0;
    while (pos->parent != NULL)
    {
        pos = pos->parent;
        cnt++;
    }
    return cnt;
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::depth(const iterator_base &base, const iterator_base &root)
{
    tree_node *pos = base.node;
    assert(pos != NULL);
    int cnt = 0;
    while (pos->parent != NULL && pos != root.node)
    {
        pos = pos->parent;
        cnt++;
    }
    return cnt;
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::max_depth() const
{
    int max_d = -1;
    for (tree_node *it = head->next_sibling; it != feet; it = it->next_sibling)
    {
        max_d = max(max_d, max_depth(it));
    }
    return max_d;
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::max_depth(const iterator_base &base) const
{
    tree_node *t = base.node;
    if (t == NULL || t == head || t == feet)
    {
        return -1;
    }

    int current_depth = 0;
    int max_depth = 0;
    while (true)
    {
        while (t->first_child == NULL)
        {
            if (t == base.node)
            {
                return max_depth;
            }
            if (t->next_sibling == NULL)
            {
                do
                {
                    t = t->parent;
                    if (t == NULL)
                    {
                        return max_depth;
                    }
                    current_depth--;
                } while (t->next_sibling == NULL);
            }
            if (t == base.node)
            {
                return max_depth;
            }
            t = t->next_sibling;
        }
        t = t->first_child;
        current_depth++;
        max_depth = max(current_depth, max_depth);
    }
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::children_count(const iterator_base &base)
{
    tree_node *pos = base.node->first_child;
    int cnt = 0;
    while (pos != NULL)
    {
        pos = pos->next_sibling;
        cnt++;
    }
    return cnt;
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::siblings_count(const iterator_base &base) const
{
    tree_node *pos = base.node;
    int cnt = 0;
    while (pos->next_sibling != NULL && pos->next_sibling != head && pos->next_sibling != feet)
    {
        cnt++;
        pos = pos->next_sibling;
    }
    pos = base.node;
    while (pos->prev_sibling != NULL && pos->prev_sibling != head && pos->prev_sibling != feet)
    {
        cnt++;
        pos = pos->prev_sibling;
    }
    return cnt;
}

template <class value_type, class allocator_type>
bool tree<value_type, allocator_type>::is_in_subtree(const iterator_base &base, const iterator_base &begin, const iterator_base &end) const
{
    pre_order_iterator t = begin;
    while (t != end)
    {
        if (t == base)
        {
            return true;
        }
        t++;
    }
    return false;
}

template <class value_type, class allocator_type>
bool tree<value_type, allocator_type>::is_valid(const iterator_base &base) const
{
    return base.node != NULL && base.node != feet && base.node != head;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::pre_order_iterator tree<value_type, allocator_type>::lowest_common_ancestor(const iterator_base &one, const iterator_base &two) const
{
    std::list<pre_order_iterator> visited;
    pre_order_iterator pos = one;
    while (is_valid(pos.node->parent))
    {
        pos = pos.node->parent;
        visited.push_back(pos);
    }
    pos = two;
    while (is_valid(pos.node->parent))
    {
        pos = pos.node->parent;
        if (find(visited.begin(), visited.end(), pos) != visited.end())
        {
            break;
        }
    }
    return pos;
}

template <class value_type, class allocator_type>
int tree<value_type, allocator_type>::index(sibling_iterator sib) const
{
    int index = 0;
    if (sib.node->parent == NULL)
    {
        while (sib.node->prev_sibling != head)
        {
            sib.node = sib.node->prev_sibling;
            index++;
        }
    }
    else
    {
        while (sib.node->prev_sibling != NULL)
        {
            sib.node = sib.node->prev_sibling;
            index++;
        }
    }
    return index;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::child(const iterator_base &base, int n)
{
    tree_node *t = base.node->first_child;
    while (n--)
    {
        assert(t != NULL);
        t = t->next_sibling;
    }
    return t;
}

template <class value_type, class allocator_type>
typename tree<value_type, allocator_type>::sibling_iterator tree<value_type, allocator_type>::sibling(const iterator_base &base, int n)
{
    tree_node *t = base.node->parent == NULL ? head->next_sibling : base.node->parent->first_child;
    while (n--)
    {
        t = t->next_sibling;
    }
    return t;
}

//

//

//

//

//

//

//

//

//

//

//

//

//

//

//

#pragma endregion
