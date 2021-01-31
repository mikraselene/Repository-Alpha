#include <iostream>
#include <vector>
#include <set>
using namespace std;
#define NODE_VALUES_NUMBER 100
#define nowhere -1

template <class T>
class template_def
{
public:
};

template <class T>
class btree_node
{
public:
    using this_type = T;
    using btree_type = btree_node<T>;

    using key_type = typename T::key_type;
    using data_type = typename T::data_type;
    using value_type = typename T::value_type;
    using size_type = typename T::size_type;

    using pointer = typename T::pointer;
    using const_pointer = typename T::const_pointer;
    using reference = typename T::reference;
    using const_reference = typename T::const_reference;

    using allocator_type = typename T::allocator_type;

    class base_fields
    {
        using field_type = typename T::node_count_type;
        bool is_leaf;         // indicating whether the node is a leaf
        field_type position;  // the position of the node
        field_type max_count; // the maximum number of values
        field_type count;     // the number of values in the node
        btree_node *parent;   // the parent of the node
    };
    class leaves : public base_fields
    {
        vector<value_type> values[NODE_VALUES_NUMBER];
    };
    class internals : public leaves
    {
        vector<btree_node *> children[NODE_VALUES_NUMBER + 1];
    };
    class tree_root : public internals
    {
        btree_node *rightmost;
        int size;
    };

public:
    auto get_parent() const -> btree_node *;
    bool is_root() const;
    void make_root();
    auto rightmost() const -> btree_node *;

    auto key(int) const -> const key_type &;
    auto value(int) -> reference;
    auto value(int) const -> const_reference;
    void swap_value(int, btree_node *, int);
    void swap_value(int, btree_node *);
    void swap_value(int, int);
    void move_value(int, btree_node *, int);
    void move_value(int, btree_node *);
    void move_value(int, int);

    void destory();

    auto child(int) const -> btree_node *;
    void reset_child(int);
    void set_child(int, btree_node *);
    void swap_child(int, btree_node *);
    void swap_child(int, btree_node *, int);
    void swap_child(int, int);
    void move_child(int, btree_node *, int);
    void move_child(int, btree_node *);
    void move_child(int, int);

    auto init_leaf(leaves *, btree_node *, int) -> btree_node *;
    auto init_internal(internals *, btree_node *) -> btree_node *;
    auto init_root(tree_root *, btree_node *) -> btree_node *;

    bool is_leaf() const;
    auto position() const -> int;
    auto count() const -> int;
    void set_count(int);
    auto max_count() const -> int;
    // auto size() const -> size_type;
    template <class... Args>
    void insert_value(int, Args &&...);
    void remove_value(int);
    void rebalance_right_to_left(btree_node *, int);
    void rebalance_left_to_right(btree_node *, int);
    void split(btree_node *, int);
    void merge(btree_node *);
    void swap(btree_node *);

private:
    btree_node(const btree_node &);
    void operator=(const btree_node &);
    template <class... Args>
    void construct_value(value_type *, Args &&...);
    template <class... Args>
    void construct_value(int, Args &&...);
    void destroy_value(value_type *);
    void destroy_value(int);
};

#pragma region

template <class T>
auto btree_node<T>::get_parent() const -> btree_node *
{
    return nullptr;
}
template <class T>
bool btree_node<T>::is_root() const
{
    return false;
}
template <class T>
void btree_node<T>::make_root()
{
}
template <class T>
auto btree_node<T>::rightmost() const -> btree_node *
{
    return nullptr;
}
template <class T>
auto btree_node<T>::key(int) const -> const key_type &
{
    return 0;
}
template <class T>
auto btree_node<T>::value(int) -> reference
{
    return nullptr;
}
template <class T>
auto btree_node<T>::value(int) const -> const_reference
{
    return nullptr;
}
template <class T>
void btree_node<T>::swap_value(int, btree_node *, int)
{
}
template <class T>
void btree_node<T>::swap_value(int, btree_node *)
{
}
template <class T>
void btree_node<T>::swap_value(int, int)
{
}
template <class T>
void btree_node<T>::move_value(int, btree_node *, int)
{
}
template <class T>
void btree_node<T>::move_value(int, btree_node *)
{
}
template <class T>
void btree_node<T>::move_value(int, int)
{
}
template <class T>
void btree_node<T>::destory()
{
}
template <class T>
auto btree_node<T>::child(int) const -> btree_node *
{
    return nullptr;
}
template <class T>
void btree_node<T>::reset_child(int)
{
}
template <class T>
void btree_node<T>::set_child(int, btree_node *)
{
}
template <class T>
void btree_node<T>::swap_child(int, btree_node *)
{
}
template <class T>
void btree_node<T>::swap_child(int, btree_node *, int)
{
}
template <class T>
void btree_node<T>::swap_child(int, int)
{
}
template <class T>
void btree_node<T>::move_child(int, btree_node *, int)
{
}
template <class T>
void btree_node<T>::move_child(int, btree_node *)
{
}
template <class T>
void btree_node<T>::move_child(int, int)
{
}
template <class T>
auto btree_node<T>::init_leaf(btree_node::leaves *, btree_node *, int) -> btree_node *
{
    return nullptr;
}
template <class T>
auto btree_node<T>::init_internal(btree_node::internals *, btree_node *) -> btree_node *
{
    return nullptr;
}
template <class T>
auto btree_node<T>::init_root(btree_node::tree_root *, btree_node *) -> btree_node *
{
    return nullptr;
}
template <class T>
bool btree_node<T>::is_leaf() const
{
    return false;
}
template <class T>
auto btree_node<T>::position() const -> int
{
    return 0;
}
template <class T>
auto btree_node<T>::count() const -> int
{
    return 0;
}
template <class T>
void btree_node<T>::set_count(int)
{
}
template <class T>
auto btree_node<T>::max_count() const -> int
{
    return 0;
}
template <class T>
template <class... Args>
void btree_node<T>::insert_value(int, Args &&...)
{
}
template <class T>
void btree_node<T>::remove_value(int)
{
}
template <class T>
void btree_node<T>::rebalance_right_to_left(btree_node *, int)
{
}
template <class T>
void btree_node<T>::rebalance_left_to_right(btree_node *, int)
{
}
template <class T>
void btree_node<T>::split(btree_node *, int)
{
}
template <class T>
void btree_node<T>::merge(btree_node *)
{
}
template <class T>
void btree_node<T>::swap(btree_node *)
{
}
template <class T>
btree_node<T>::btree_node(const btree_node &)
{
}
template <class T>
void btree_node<T>::operator=(const btree_node &)
{
}
template <class T>
template <class... Args>
void btree_node<T>::construct_value(value_type *, Args &&...)
{
}
template <class T>
template <class... Args>
void btree_node<T>::construct_value(int, Args &&...)
{
}
template <class T>
void btree_node<T>::destroy_value(value_type *)
{
}
template <class T>
void btree_node<T>::destroy_value(int)
{
}

#pragma endregion

template <class Node, class Ref, class Ptr>
class btree_iterator
{
public:
    using node_type = Node;
    using reference = Ref;
    using pointer = Ptr;
    using params_type = typename Node ::params_type;

    using normal_node = Node; // FIXME:
    using normal_reference = typename params_type::reference;
    using normal_pointer = typename params_type::pointer;
    using iterator = btree_iterator<normal_node, normal_reference, normal_pointer>;

    using const_node = const Node;
    using const_reference = typename params_type::const_reference;
    using const_pointer = typename params_type::const_pointer;
    using const_iterator = btree_iterator<const_node, const_reference, const_pointer>;

    using iterator_type = btree_iterator<Node, Ref, Ptr>;

    btree_iterator() : node(nullptr), position(nowhere) {}
    btree_iterator(const iterator &that) : node(that.node), position(that.position) {}

    auto operator==(const const_iterator &x) -> bool const
    {
        return node == x.node && position == x.position;
    }
    auto operator!=(const const_iterator &x) -> bool const
    {
        return node != x.node || position != x.position;
    }

    auto operator*() -> reference const
    {
        return node->value(position);
    }
    auto operator->() -> pointer const
    {
        return &node->value(position);
    }

    auto operator++() -> iterator_type &
    {
    }
    auto operator--() -> iterator_type &
    {
    }
    auto operator++(int) -> iterator_type
    {
        auto temp = *this;
        ++*this;
        return temp;
    }
    auto operator--(int) -> iterator_type
    {
        auto temp = *this;
        --*this;
        return temp;
    }

    normal_node node;
    int position;
};

#pragma region

#pragma endregion

template <class T>
class btree
{
public:
    using btree_type = btree<T>;
    using node_type = btree_node<T>;
    using base_fields = typename node_type::base_fields;
    using leaves = typename node_type::leaves;
    using internals = typename node_type::internals;
    using tree_root = typename node_type::tree_root;

    using key_compare = typename node_type::key_compare; // FIXME:

    using param_type = T;
    using key_type = typename T::key_type;
    using value_type = typename T::value_type;
    using data_type = typename T::data_type;
    using size_type = typename T::size_type;
    using allocator_type = typename T::allocator_type;
    using internal_allocator_type = typename T::internal_allocator_type;
    using pointer = typename T::pointer;
    using const_pointer = typename T::const_pointer;
    using reference = typename T::reference;
    using const_reference = typename T::const_reference;

    using iterator = btree_iterator<node_type, reference, pointer>;
    using const_iterator = typename iterator::const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
    btree();
    btree(const btree_type &x);
    ~btree();

    auto begin() -> iterator;
    auto begin() const -> const_iterator;
    auto cbegin() const -> const_iterator;
    auto end() -> iterator;
    auto end() const -> const_iterator;
    auto cend() const -> const_iterator;
    auto rbegin() -> reverse_iterator;
    auto rbegin() const -> const_reverse_iterator;
    auto crbegin() const -> const_reverse_iterator;
    auto rend() -> reverse_iterator;
    auto rend() const -> const_reverse_iterator;
    auto crend() const -> const_reverse_iterator;

    auto lower_bound(const key_type &key) -> iterator;
    auto lower_bound(const key_type &key) const -> const_iterator;
    auto upper_bound(const key_type &key) -> iterator;
    auto upper_bound(const key_type &key) const -> const_iterator;
    auto equal_range(const key_type &key) -> pair<iterator, iterator>;
    auto equal_range(const key_type &key) const -> pair<const_iterator, const_iterator>;

    template <class... Args>
    auto emplace_unique_key_args(const key_type &, Args &&...) -> iterator;
    template <class P>
    auto emplace_unique(P &&) -> iterator;
    template <class F, class S>
    auto emplace_unique(F &&, S &&) -> iterator;
    template <class... Args>
    auto emplace_unique(Args &&...) -> iterator;
    template <class... Args>
    auto emplace_hint_unique_key_args(const_iterator, const key_type &, Args &&...) -> iterator;
    template <class P>
    auto emplace_hint_unique(const_iterator, P &&) -> iterator;
    template <class F, class S>
    auto emplace_hint_unique(const_iterator, F &&, S &&) -> iterator;
    template <class... Args>
    auto emplace_hint_unique(const_iterator, Args &&...) -> iterator;

    auto insert_unique(const value_type &) -> iterator;
    auto insert_unique(value_type &&) -> iterator;
    auto insert_unique(const_iterator, const value_type &) -> iterator;
    auto insert_unique(const_iterator, value_type &&) -> iterator;
    template <class P>
    auto insert_unique(P &&) -> iterator;
    template <class P>
    auto insert_unique(const_iterator, P &&) -> iterator;

    template <class... Args>
    auto emplace_multi_key_args(const key_type &, Args &&...) -> iterator;
    template <class... Args>
    auto emplace_multi(Args &&...) -> iterator;
    template <class... Args>
    auto emplace_hint_multi_key_args(const_iterator, const key_type &, Args &&...) -> iterator;
    template <class... Args>
    auto emplace_hint_multi(const_iterator, Args &&...) -> iterator;

    auto insert_multi(const value_type &) -> iterator;
    auto insert_multi(value_type &&) -> iterator;
    auto insert_multi(const_iterator, const value_type &) -> iterator;
    auto insert_multi(const_iterator, value_type &&) -> iterator;
    template <class P>
    auto insert_multi(P &&) -> iterator;
    template <class P>
    auto insert_multi(const_iterator, P &&) -> iterator;

    auto erase(const_iterator a, const_iterator b) -> int;
    auto erase_unique(const key_type &) -> int;
    auto erase_multi(const key_type &) -> int;

    auto find_unique(const key_type &) -> iterator;
    auto find_unique(const key_type &) const -> const_iterator;
    auto find_multi(const key_type &) -> iterator;
    auto find_multi(const key_type &) const -> const_iterator;

    auto count_unique(const key_type &) const -> size_type;
    auto count_multi(const key_type &) const -> size_type;

    auto size() const -> size_type;
    auto max_size() const -> size_type;
    auto leaf_nodes() const -> size_type;
    auto internal_nodes() const -> size_type;
    auto nodes() const -> size_type;
    auto height() -> size_type;

    auto bytes_used() const -> size_type;
    auto average_bytes_per_value() -> double;
    auto fullness() const -> double;
    auto overhead() const -> double;

    void assign(const btree_type &);
    void swap(btree_type &);
    auto key_comp() const -> const key_compare &;
    bool compare_keys(const key_type &, const key_type &) const;
    void dump(ostream &) const;
    void verify() const;
    bool empty() const;
    void clear();
    auto operator=(const btree_type &) -> btree_type &;

private:
    auto root() -> node_type *;
    auto root() const -> const node_type *;
    auto rightmost() -> node_type *;
    auto rightmost() const -> const node_type *;
    auto leftmost() -> node_type *;
    auto leftmost() const -> const node_type *;

    auto new_internal_node(node_type *) -> node_type *;
    auto new_internal_root_node() -> node_type *;
    auto new_leaf_node(node_type *) -> node_type *;
    auto new_leaf_node(int) -> node_type *;

    void delete_leaf_node(node_type *);
    void delete_internal_root_node();
    void delete_internal_node(node_type *);

    auto internal_allocator() const noexcept -> const internal_allocator_type &;
    auto allocator() const noexcept -> allocator_type;

    bool try_merge_or_rebalance(const_iterator &);
    void try_shrink();

    auto internal_end(const_iterator) -> iterator;
    auto internal_end(const_iterator) const -> const_iterator;
    template <class... Args>
    auto internal_emplace(const_iterator, Args &&...) -> iterator;
    template <class IterType>
    auto internal_last(IterType) -> IterType;
    template <class IterType>
    auto internal_locate(const key_type &, IterType) const -> pair<IterType, int>;
    template <class IterType>
    auto internal_locate_plain_compare(const key_type &, IterType) const -> pair<IterType, int>;
    template <class IterType>
    auto internal_locate_compare_to(const key_type &, IterType) const -> pair<IterType, int>;
    template <class IterType>
    auto internal_lower_bound(const key_type &, IterType) const -> IterType;
    template <class IterType>
    auto internal_upper_bound(const key_type &, IterType) const -> IterType;
    template <class IterType>
    auto internal_find_unique(const key_type &, IterType) const -> IterType;
    template <class IterType>
    auto internal_find_multi(const key_type &, IterType) const -> IterType;

    void internal_clear(node_type *);
    void internal_dump(ostream &, const node_type *, int) const;
    auto internal_verify(const node_type *, const key_type *, const key_type *) const -> int;
    // auto internal_stats(const node_type *) const -> node_stats;
};

#pragma region // implementation of `btree`

template <class T>
btree<T>::btree()
{
}
template <class T>
btree<T>::btree(const btree::btree_type &x)
{
}
template <class T>
btree<T>::~btree()
{
}
template <class T>
auto btree<T>::begin() -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::begin() const -> btree::const_iterator
{
    return nullptr;
}
template <class T>
auto btree<T>::cbegin() const -> btree::const_iterator
{
    return nullptr;
}
template <class T>
auto btree<T>::end() -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::end() const -> btree::const_iterator
{
    return nullptr;
}
template <class T>
auto btree<T>::cend() const -> btree::const_iterator
{
    return nullptr;
}
template <class T>
auto btree<T>::rbegin() -> reverse_iterator
{
    return btree::reverse_iterator();
}
template <class T>
auto btree<T>::rbegin() const -> std::reverse_iterator<btree::const_iterator>
{
    return nullptr;
}
template <class T>
auto btree<T>::crbegin() const -> std::reverse_iterator<btree::const_iterator>
{
    return nullptr;
}
template <class T>
auto btree<T>::rend() -> reverse_iterator
{
    return btree::reverse_iterator();
}
template <class T>
auto btree<T>::rend() const -> std::reverse_iterator<btree::const_iterator>
{
    return nullptr;
}
template <class T>
auto btree<T>::crend() const -> std::reverse_iterator<btree::const_iterator>
{
    return nullptr;
}
template <class T>
auto btree<T>::lower_bound(const key_type &key) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::lower_bound(const key_type &key) const -> btree::const_iterator
{
    return nullptr;
}
template <class T>
auto btree<T>::upper_bound(const key_type &key) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::upper_bound(const key_type &key) const -> btree::const_iterator
{
    return nullptr;
}
template <class T>
auto btree<T>::equal_range(const key_type &key) -> pair<iterator, iterator>
{
    return pair<iterator, iterator>();
}
template <class T>
auto btree<T>::equal_range(const key_type &key) const -> pair<btree::const_iterator, btree::const_iterator>
{
    return nullptr;
}
template <class T>
template <class... Args>
auto btree<T>::emplace_unique_key_args(const key_type &, Args &&...) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class P>
auto btree<T>::emplace_unique(P &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class F, class S>
auto btree<T>::emplace_unique(F &&, S &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class... Args>
auto btree<T>::emplace_unique(Args &&...) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class... Args>
auto btree<T>::emplace_hint_unique_key_args(btree::const_iterator, const key_type &, Args &&...) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class P>
auto btree<T>::emplace_hint_unique(btree::const_iterator, P &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class F, class S>
auto btree<T>::emplace_hint_unique(btree::const_iterator, F &&, S &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class... Args>
auto btree<T>::emplace_hint_unique(btree::const_iterator, Args &&...) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::insert_unique(const value_type &) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::insert_unique(value_type &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::insert_unique(btree::const_iterator, const value_type &) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::insert_unique(btree::const_iterator, value_type &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class P>
auto btree<T>::insert_unique(P &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class P>
auto btree<T>::insert_unique(btree::const_iterator, P &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class... Args>
auto btree<T>::emplace_multi_key_args(const key_type &, Args &&...) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class... Args>
auto btree<T>::emplace_multi(Args &&...) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class... Args>
auto btree<T>::emplace_hint_multi_key_args(btree::const_iterator, const key_type &, Args &&...) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class... Args>
auto btree<T>::emplace_hint_multi(btree::const_iterator, Args &&...) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::insert_multi(const value_type &) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::insert_multi(value_type &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::insert_multi(btree::const_iterator, const value_type &) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::insert_multi(btree::const_iterator, value_type &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class P>
auto btree<T>::insert_multi(P &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class P>
auto btree<T>::insert_multi(btree::const_iterator, P &&) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::erase(btree::const_iterator a, btree::const_iterator b) -> int
{
    return 0;
}
template <class T>
auto btree<T>::erase_unique(const key_type &) -> int
{
    return 0;
}
template <class T>
auto btree<T>::erase_multi(const key_type &) -> int
{
    return 0;
}
template <class T>
auto btree<T>::find_unique(const key_type &) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::find_unique(const key_type &) const -> btree::const_iterator
{
    return nullptr;
}
template <class T>
auto btree<T>::find_multi(const key_type &) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::find_multi(const key_type &) const -> btree::const_iterator
{
    return nullptr;
}
template <class T>
auto btree<T>::count_unique(const key_type &) const -> size_type
{
    return nullptr;
}
template <class T>
auto btree<T>::count_multi(const key_type &) const -> size_type
{
    return nullptr;
}
template <class T>
auto btree<T>::size() const -> size_type
{
    return nullptr;
}
template <class T>
auto btree<T>::max_size() const -> size_type
{
    return nullptr;
}
template <class T>
auto btree<T>::leaf_nodes() const -> size_type
{
    return nullptr;
}
template <class T>
auto btree<T>::internal_nodes() const -> size_type
{
    return nullptr;
}
template <class T>
auto btree<T>::nodes() const -> size_type
{
    return nullptr;
}
template <class T>
auto btree<T>::height() -> size_type
{
    return nullptr;
}
template <class T>
auto btree<T>::bytes_used() const -> size_type
{
    return nullptr;
}
template <class T>
auto btree<T>::average_bytes_per_value() -> double
{
    return 0;
}
template <class T>
auto btree<T>::fullness() const -> double
{
    return 0;
}
template <class T>
auto btree<T>::overhead() const -> double
{
    return 0;
}
template <class T>
void btree<T>::assign(const btree::btree_type &)
{
}
template <class T>
void btree<T>::swap(btree::btree_type &)
{
}
template <class T>
auto btree<T>::key_comp() const -> const btree::key_compare &
{
    return 0;
}
template <class T>
bool btree<T>::compare_keys(const key_type &, const key_type &) const
{
    return false;
}
template <class T>
void btree<T>::dump(ostream &) const
{
}
template <class T>
void btree<T>::verify() const
{
}
template <class T>
bool btree<T>::empty() const
{
    return false;
}
template <class T>
void btree<T>::clear()
{
}
template <class T>
auto btree<T>::operator=(const btree::btree_type &) -> btree::btree_type &
{
    return 0;
}
template <class T>
auto btree<T>::root() -> btree::node_type *
{
    return nullptr;
}
template <class T>
auto btree<T>::root() const -> const btree::node_type *
{
    return nullptr;
}
template <class T>
auto btree<T>::rightmost() -> btree::node_type *
{
    return nullptr;
}
template <class T>
auto btree<T>::rightmost() const -> const btree::node_type *
{
    return nullptr;
}
template <class T>
auto btree<T>::leftmost() -> btree::node_type *
{
    return nullptr;
}
template <class T>
auto btree<T>::leftmost() const -> const btree::node_type *
{
    return nullptr;
}
template <class T>
auto btree<T>::new_internal_node(btree::node_type *) -> btree::node_type *
{
    return nullptr;
}
template <class T>
auto btree<T>::new_internal_root_node() -> btree::node_type *
{
    return nullptr;
}
template <class T>
auto btree<T>::new_leaf_node(btree::node_type *) -> btree::node_type *
{
    return nullptr;
}
template <class T>
auto btree<T>::new_leaf_node(int) -> btree::node_type *
{
    return nullptr;
}
template <class T>
void btree<T>::delete_leaf_node(btree::node_type *)
{
}
template <class T>
void btree<T>::delete_internal_root_node()
{
}
template <class T>
void btree<T>::delete_internal_node(btree::node_type *)
{
}
template <class T>
auto btree<T>::internal_allocator() const noexcept -> const internal_allocator_type &
{
    return 0;
}
template <class T>
auto btree<T>::allocator() const noexcept -> allocator_type
{
    return nullptr;
}
template <class T>
bool btree<T>::try_merge_or_rebalance(btree::const_iterator &)
{
    return false;
}
template <class T>
void btree<T>::try_shrink()
{
}
template <class T>
auto btree<T>::internal_end(btree::const_iterator) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
auto btree<T>::internal_end(btree::const_iterator) const -> btree::const_iterator
{
    return nullptr;
}
template <class T>
template <class... Args>
auto btree<T>::internal_emplace(btree::const_iterator, Args &&...) -> btree::iterator
{
    return btree::iterator();
}
template <class T>
template <class IterType>
auto btree<T>::internal_last(IterType) -> IterType
{
    return nullptr;
}
template <class T>
template <class IterType>
auto btree<T>::internal_locate(const key_type &, IterType) const -> pair<IterType, int>
{
    return pair<IterType, int>();
}
template <class T>
template <class IterType>
auto btree<T>::internal_locate_plain_compare(const key_type &, IterType) const -> pair<IterType, int>
{
    return pair<IterType, int>();
}
template <class T>
template <class IterType>
auto btree<T>::internal_locate_compare_to(const key_type &, IterType) const -> pair<IterType, int>
{
    return pair<IterType, int>();
}
template <class T>
template <class IterType>
auto btree<T>::internal_lower_bound(const key_type &, IterType) const -> IterType
{
    return nullptr;
}
template <class T>
template <class IterType>
auto btree<T>::internal_upper_bound(const key_type &, IterType) const -> IterType
{
    return nullptr;
}
template <class T>
template <class IterType>
auto btree<T>::internal_find_unique(const key_type &, IterType) const -> IterType
{
    return nullptr;
}
template <class T>
template <class IterType>
auto btree<T>::internal_find_multi(const key_type &, IterType) const -> IterType
{
    return nullptr;
}
template <class T>
void btree<T>::internal_clear(btree::node_type *)
{
}
template <class T>
void btree<T>::internal_dump(ostream &, const btree::node_type *, int) const
{
}
template <class T>
auto btree<T>::internal_verify(const btree::node_type *, const key_type *, const key_type *) const -> int
{
    return 0;
}

#pragma endregion
