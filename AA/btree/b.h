#ifndef BTREE_BTREE_H__
#define BTREE_BTREE_H__

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

#include <algorithm>
#include <functional>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

// Types small_ and big_ are promise that sizeof(small_) < sizeof(big_)
typedef char small_;

struct big_
{
    char dummy[2];
};

struct btree_extract_key_fail_tag
{
};
struct btree_extract_key_self_tag
{
};
struct btree_extract_key_first_tag
{
};

template <typename ValueType, typename Key,
          typename RawValueType = typename std::remove_const<typename std::remove_reference<ValueType>::type>::type>
struct btree_can_extract_key
    : std::conditional<std::is_same<RawValueType, Key>::value,
                       btree_extract_key_self_tag,
                       btree_extract_key_fail_tag>::type
{
};

template <typename _Pair, typename Key, typename First, typename Second>
struct btree_can_extract_key<_Pair, Key, std::pair<First, Second>>
    : std::conditional<std::is_same<typename std::remove_const<First>::type, Key>::value,
                       btree_extract_key_first_tag,
                       btree_extract_key_fail_tag>::type
{
};

// btree_can_extract_map_key uses true_type/false_type instead of the tags.
// It returns true if Key != ContainerValueType (the container is a map not a set)
// and ValueType == Key.
template <typename ValueType, typename Key, typename ContainerValueType,
          typename RawValueType = typename std::remove_const<typename std::remove_reference<ValueType>::type>::type>
struct btree_can_extract_map_key : std::integral_constant<bool, std::is_same<RawValueType, Key>::value>
{
};

// This specialization returns btree_extract_key_fail_tag for non-map containers
// because Key == ContainerValueType
template <typename ValueType, typename Key, typename RawValueType>
struct btree_can_extract_map_key<ValueType, Key, Key, RawValueType> : std::false_type
{
};

// A helper type used to indicate that a key-compare-to functor has been
// provided. A user can specify a key-compare-to functor by doing:
//
//  struct MyStringComparer
//      : public util::btree::btree_key_compare_to_tag {
//    int operator()(const string& a, const string& b) const {
//      return a.compare(b);
//    }
//  };
//
// Note that the return type is an int and not a bool. There is a
// COMPILE_ASSERT which enforces this return type.
struct btree_key_compare_to_tag
{
};

// A helper class that indicates if the Compare parameter is derived from
// btree_key_compare_to_tag.
template <typename Compare>
struct btree_is_key_compare_to : public std::is_convertible<Compare, btree_key_compare_to_tag>
{
};

// A helper class to convert a boolean comparison into a three-way
// "compare-to" comparison that returns a negative value to indicate
// less-than, zero to indicate equality and a positive value to
// indicate greater-than. This helper class is specialized for
// less<string> and greater<string>. The btree_key_compare_to_adapter
// class is provided so that btree users automatically get the more
// efficient compare-to code when using common google string types
// with common comparison functors.
template <typename Compare>
struct btree_key_compare_to_adapter : Compare
{
    btree_key_compare_to_adapter();
    btree_key_compare_to_adapter(const Compare &c);
    btree_key_compare_to_adapter(const btree_key_compare_to_adapter<Compare> &c);
};

template <>
struct btree_key_compare_to_adapter<std::less<std::string>> : public btree_key_compare_to_tag
{
    btree_key_compare_to_adapter();
    btree_key_compare_to_adapter(const std::less<std::string> &);
    btree_key_compare_to_adapter(const btree_key_compare_to_adapter<std::less<std::string>> &);
    int operator()(const std::string &a, const std::string &b) const;
};

template <>
struct btree_key_compare_to_adapter<std::greater<std::string>> : public btree_key_compare_to_tag
{
    btree_key_compare_to_adapter();
    btree_key_compare_to_adapter(const std::greater<std::string> &);
    btree_key_compare_to_adapter(const btree_key_compare_to_adapter<std::greater<std::string>> &);
    int operator()(const std::string &a, const std::string &b) const;
};

// A helper class that allows a compare-to functor to behave like a plain
// compare functor. This specialization is used when we do not have a
// compare-to functor.
template <typename Key, typename Compare, bool HaveCompareTo>
struct btree_key_comparer
{
    btree_key_comparer();
    btree_key_comparer(Compare c);
    static bool bool_compare(const Compare &comp, const Key &x, const Key &y);
    bool operator()(const Key &x, const Key &y) const;
    Compare comp;
};

// A specialization of btree_key_comparer when a compare-to functor is
// present. We need a plain (boolean) comparison in some parts of the btree
// code, such as insert-with-hint.
template <typename Key, typename Compare>
struct btree_key_comparer<Key, Compare, true>
{
    btree_key_comparer() {}
    btree_key_comparer(Compare c) : comp(c) {}
    static bool bool_compare(const Compare &comp, const Key &x, const Key &y);
    bool operator()(const Key &x, const Key &y) const;
    Compare comp;
};

// A helper function to compare to keys using the specified compare
// functor. This dispatches to the appropriate btree_key_comparer comparison,
// depending on whether we have a compare-to functor or not (which depends on
// whether Compare is derived from btree_key_compare_to_tag).
template <typename Key, typename Compare>
static bool btree_compare_keys(const Compare &comp, const Key &x, const Key &y);

template <typename Key, typename Compare,
          typename Alloc, int TargetNodeSize, int ValueSize>
struct btree_common_params
{
    // If Compare is derived from btree_key_compare_to_tag then use it as the
    // key_compare type. Otherwise, use btree_key_compare_to_adapter<> which will
    // fall-back to Compare if we don't have an appropriate specialization.
    typedef std::conditional_t<btree_is_key_compare_to<Compare>::value,
                               Compare,
                               btree_key_compare_to_adapter<Compare>>
        key_compare;
    // A type which indicates if we have a key-compare-to functor or a plain old
    // key-compare functor.
    typedef btree_is_key_compare_to<key_compare> is_key_compare_to;

    typedef Key key_type;
    typedef ssize_t size_type;
    typedef ptrdiff_t difference_type;

    typedef Alloc allocator_type;
    typedef std::allocator_traits<allocator_type> allocator_traits;
    typedef typename allocator_traits::template rebind_alloc<char> internal_allocator_type;
    typedef std::allocator_traits<internal_allocator_type> internal_allocator_traits;

    enum
    {
        kTargetNodeSize = TargetNodeSize,

        // Available space for values.  This is largest for leaf nodes,
        // which has overhead no fewer than two pointers.
        kNodeValueSpace = TargetNodeSize - 2 * sizeof(void *),
    };

    // This is an integral type large enough to hold as many
    // ValueSize-values as will fit a node of TargetNodeSize bytes.
    typedef std::conditional_t<(kNodeValueSpace / ValueSize) >= 256,
                               uint16_t,
                               uint8_t>
        node_count_type;
};

// A parameters structure for holding the type parameters for a map.
template <typename Key, typename Data, typename Compare, typename Alloc, int TargetNodeSize>
struct btree_map_params : public btree_common_params<Key, Compare, Alloc, TargetNodeSize, sizeof(Key) + sizeof(Data)>
{
    typedef Data data_type;
    typedef Data mapped_type;
    typedef std::pair<const Key, data_type> value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;

    enum
    {
        kValueSize = sizeof(Key) + sizeof(data_type),
    };

    static void swap(value_type &a, value_type &b);

    static const Key &get_key(const value_type &x);
};

// A parameters structure for holding the type parameters for a btree_set.
template <typename Key, typename Compare, typename Alloc, int TargetNodeSize>
struct btree_set_params : public btree_common_params<Key, Compare, Alloc, TargetNodeSize, sizeof(Key)>
{
    typedef std::false_type data_type;
    typedef std::false_type mapped_type;
    typedef Key value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;

    enum
    {
        kValueSize = sizeof(Key),
    };

    static void swap(value_type &a, value_type &b);

    static const Key &get_key(const value_type &x);
};

// An adapter class that converts a lower-bound compare into an upper-bound
// compare.
template <typename Key, typename Compare>
struct btree_upper_bound_adapter : public Compare
{
    btree_upper_bound_adapter(Compare c);
    bool operator()(const Key &a, const Key &b) const;
};

template <typename Key, typename CompareTo>
struct btree_upper_bound_compare_to_adapter : public CompareTo
{
    btree_upper_bound_compare_to_adapter(CompareTo c);
    int operator()(const Key &a, const Key &b) const;
};

// Dispatch helper class for using linear search with plain compare.
template <typename K, typename N, typename Compare>
struct btree_linear_search_plain_compare
{
    static int lower_bound(const K &k, const N &n, Compare comp);
    static int upper_bound(const K &k, const N &n, Compare comp);
};

// Dispatch helper class for using linear search with compare-to
template <typename K, typename N, typename CompareTo>
struct btree_linear_search_compare_to
{
    static int lower_bound(const K &k, const N &n, CompareTo comp);
    static int upper_bound(const K &k, const N &n, CompareTo comp);
};

// Dispatch helper class for using binary search with plain compare.
template <typename K, typename N, typename Compare>
struct btree_binary_search_plain_compare
{
    static int lower_bound(const K &k, const N &n, Compare comp);
    static int upper_bound(const K &k, const N &n, Compare comp);
};

// Dispatch helper class for using binary search with compare-to.
template <typename K, typename N, typename CompareTo>
struct btree_binary_search_compare_to
{
    static int lower_bound(const K &k, const N &n, CompareTo /*comp*/);
    static int upper_bound(const K &k, const N &n, CompareTo comp);
};

// Dispatch helper class for using btree::internal_locate with plain compare.
struct btree_internal_locate_plain_compare
{
    template <typename K, typename T, typename Iter>
    static std::pair<Iter, int> dispatch(const K &k, const T &t, Iter iter);
};

// Dispatch helper class for using btree::internal_locate with compare-to.
struct btree_internal_locate_compare_to
{
    template <typename K, typename T, typename Iter>
    static std::pair<Iter, int> dispatch(const K &k, const T &t, Iter iter);
};

// A node in the btree holding. The same node type is used for both internal
// and leaf nodes in the btree, though the nodes are allocated in such a way
// that the children array is only valid in internal nodes.
template <typename Params>
class btree_node
{
public:
    typedef Params params_type;
    typedef btree_node<Params> self_type;
    typedef typename Params::key_type key_type;
    typedef typename Params::data_type data_type;
    typedef typename Params::value_type value_type;
    typedef typename Params::pointer pointer;
    typedef typename Params::const_pointer const_pointer;
    typedef typename Params::reference reference;
    typedef typename Params::const_reference const_reference;
    typedef typename Params::key_compare key_compare;
    typedef typename Params::size_type size_type;
    typedef typename Params::difference_type difference_type;

    typedef typename Params::allocator_type allocator_type;
    typedef typename Params::allocator_traits allocator_traits;

    // Typedefs for the various types of node searches.
    typedef btree_linear_search_plain_compare<key_type, self_type, key_compare> linear_search_plain_compare_type;
    typedef btree_linear_search_compare_to<key_type, self_type, key_compare> linear_search_compare_to_type;
    typedef btree_binary_search_plain_compare<key_type, self_type, key_compare> binary_search_plain_compare_type;
    typedef btree_binary_search_compare_to<key_type, self_type, key_compare> binary_search_compare_to_type;
    // If we have a valid key-compare-to type, use linear_search_compare_to,
    // otherwise use linear_search_plain_compare.
    typedef std::conditional_t<Params::is_key_compare_to::value,
                               linear_search_compare_to_type,
                               linear_search_plain_compare_type>
        linear_search_type;
    // If we have a valid key-compare-to type, use binary_search_compare_to,
    // otherwise use binary_search_plain_compare.
    typedef std::conditional_t<Params::is_key_compare_to::value,
                               binary_search_compare_to_type,
                               binary_search_plain_compare_type>
        binary_search_type;
    // If the key is an integral or floating point type, use linear search which
    // is faster than binary search for such types. Might be wise to also
    // configure linear search based on node-size.
    typedef std::conditional_t<std::is_integral<key_type>::value || std::is_floating_point<key_type>::value,
                               linear_search_type, binary_search_type>
        search_type;

    struct base_fields
    {
        typedef typename Params::node_count_type field_type;

        // A boolean indicating whether the node is a leaf or not.
        bool leaf;
        // The position of the node in the node's parent.
        field_type position;
        // The maximum number of values the node can hold.
        field_type max_count;
        // The count of the number of values in the node.
        field_type count;
        // A pointer to the node's parent.
        btree_node *parent;
    };

    enum
    {
        kValueSize = params_type::kValueSize,
        kTargetNodeSize = params_type::kTargetNodeSize,

        // Compute how many values we can fit onto a leaf node.
        kNodeTargetValues = (kTargetNodeSize - sizeof(base_fields)) / kValueSize,
        // We need a minimum of 3 values per internal node in order to perform
        // splitting (1 value for the two nodes involved in the split and 1 value
        // propagated to the parent as the delimiter for the split).
        kNodeValues = kNodeTargetValues >= 3 ? kNodeTargetValues : 3,

        kExactMatch = 1 << 30,
        kMatchMask = kExactMatch - 1,
    };

    struct leaf_fields : public base_fields
    {
        // The array of values. Only the first count of these values have been
        // constructed and are valid.
        value_type values[kNodeValues];
    };

    struct internal_fields : public leaf_fields
    {
        // The array of child pointers. The keys in children_[i] are all less than
        // key(i). The keys in children_[i + 1] are all greater than key(i). There
        // are always count + 1 children.
        btree_node *children[kNodeValues + 1];
    };

    struct root_fields : public internal_fields
    {
        btree_node *rightmost;
        size_type size;
    };

public:
    // Getter/setter for whether this is a leaf node or not. This value doesn't
    // change after the node is created.
    bool is_leaf() const;

    // Getter for the position of this node in its parent.
    int position() const;

    // Getter/setter for the number of values stored in this node.
    int count() const;
    void set_count(int v);
    int max_count() const;

    // Getter for the parent of this node.
    btree_node *get_parent() const;
    // Getter for whether the node is the root of the tree. The parent of the
    // root of the tree is the leftmost node in the tree which is guaranteed to
    // be a leaf.
    bool is_root() const;
    void make_root();

    // Getter for the rightmost root node field. Only valid on the root node.
    btree_node *rightmost() const;
    btree_node *&__rightmost();

    // Getter for the size root node field. Only valid on the root node.
    size_type size() const;
    size_type &__size();

    // Getters for the key/value at position i in the node.
    const key_type &key(int i) const;
    reference value(int i);
    const_reference value(int i) const;

    // Swap value i in this node with value j in node x.
    void swap_value(int i, btree_node *x, int j);

    // Swap value i in this node with value i in node x.
    void swap_value(int i, btree_node *x);

    // Swap value i with value j.
    void swap_value(int i, int j);
    // Move value i in this node to value j in node x.
    void move_value(int i, btree_node *x, int j);

    // Move value i in this node to value i in node x.
    void move_value(int i, btree_node *x);

    // Move value i to value j.
    void move_value(int i, int j);

    // Getters/setter for the child at position i in the node.
    btree_node *child(int i) const;

#ifndef NDEBUG
    void reset_child(int i);
#else
    void reset_child(int);
#endif

    void set_child(int i, btree_node *c);

    // Swap child i in this node with child j in node x.
    void swap_child(int i, btree_node *x, int j);

    // Swap child i in this node with child i in node x.
    void swap_child(int i, btree_node *x);

    // Swap child i with child j.
    void swap_child(int i, int j);

    // Move child i in this node to child j in node x.
    void move_child(int i, btree_node *x, int j);

    // Move child i in this node to child i in node x.
    void move_child(int i, btree_node *x);

    // Move child i to child j.
    void move_child(int i, int j);

    // Returns the position of the first value whose key is not less than k.
    template <typename Compare>
    int lower_bound(const key_type &k, const Compare &comp) const;
    // Returns the position of the first value whose key is greater than k.
    template <typename Compare>
    int upper_bound(const key_type &k, const Compare &comp) const;

    // Returns the position of the first value whose key is not less than k
    // using linear search performed using plain compare.
    template <typename Compare>
    int linear_search_plain_compare(const key_type &k, int s, int e, const Compare &comp) const;

    // Returns the position of the first value whose key is not less than k
    // using linear search performed using compare-to.
    template <typename Compare>
    int linear_search_compare_to(const key_type &k, int s, int e, const Compare &comp) const;

    // Returns the position of the first value whose key is not less than k
    // using binary search performed using plain compare.
    template <typename Compare>
    int binary_search_plain_compare(const key_type &k, int s, int e, const Compare &comp) const;

    // Returns the position of the first value whose key is not less than k
    // using binary search performed using compare-to.
    template <typename CompareTo>
    int binary_search_compare_to(const key_type &k, int s, int e, const CompareTo &comp) const;

    // Inserts the value x at position i, shifting all existing values
    // and children at positions >= i to the right by 1.
    template <typename... Args>
    inline void insert_value(int i, Args &&... args);

    // Removes the value at position i, shifting all existing values
    // and children at positions > i to the left by 1.
    inline void remove_value(int i);

    // Rebalances a node with its right sibling.
    void rebalance_right_to_left(btree_node *src, int to_move);
    void rebalance_left_to_right(btree_node *dst, int to_move);

    // Splits a node, moving a portion of the node's values to its right sibling.
    void split(btree_node *dst, int insert_position);

    // Merges a node with its right sibling, moving all of the values
    // and the delimiting key in the parent node onto itself.
    void merge(btree_node *src);

    // Swap the contents of "this" and "src".
    void swap(btree_node *x);

    // Node allocation/deletion routines.
    static btree_node *init_leaf(leaf_fields *f, btree_node *parent, int max_count);

    static btree_node *init_internal(internal_fields *f, btree_node *parent);

    static btree_node *init_root(root_fields *f, btree_node *parent);

    void destroy();

private:
    static constexpr const char zero_value[sizeof(value_type)] = {};

    template <typename... Args>
    void construct_value(value_type *v, Args &&... args);

    template <typename... Args>
    void construct_value(int i, Args &&... args);

    void destroy_value(value_type *v);

    void destroy_value(int i);

private:
    root_fields fields_;

private:
    btree_node(const btree_node &);
    void operator=(const btree_node &);
};

template <typename Node, typename Reference, typename Pointer>
class btree_iterator
{
public:
    typedef typename Node::key_type key_type;
    typedef typename Node::size_type size_type;
    typedef typename Node::difference_type difference_type;
    typedef typename Node::params_type params_type;

    typedef Node node_type;
    typedef typename std::remove_const<Node>::type normal_node;
    typedef const Node const_node;
    typedef typename params_type::value_type value_type;
    typedef typename params_type::pointer normal_pointer;
    typedef typename params_type::reference normal_reference;
    typedef typename params_type::const_pointer const_pointer;
    typedef typename params_type::const_reference const_reference;

    typedef Pointer pointer;
    typedef Reference reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    typedef btree_iterator<normal_node, normal_reference, normal_pointer> iterator;
    typedef btree_iterator<const_node, const_reference, const_pointer> const_iterator;
    typedef btree_iterator<Node, Reference, Pointer> self_type;

    btree_iterator();
    btree_iterator(const iterator &x);

    bool operator==(const const_iterator &x) const;
    bool operator!=(const const_iterator &x) const;

    // Accessors for the key/value the iterator is pointing at.
    const key_type &key() const;
    reference operator*() const;
    pointer operator->() const;

    self_type &operator++();
    self_type &operator--();
    self_type operator++(int);
    self_type operator--(int);

private:
    btree_iterator(Node *n, int p);

    // Increment/decrement the iterator.
    void increment();
    void increment_by(int count);
    void increment_slow();

    void decrement();
    void decrement_slow();

    // The node in the tree the iterator is pointing at.
    normal_node *node;
    // The position within the node of the tree the iterator is pointing at.
    int position;

    template <typename>
    friend class btree;
    friend iterator;
    friend const_iterator;
};

template <typename Params>
class btree : public Params::key_compare
{
    typedef btree<Params> self_type;
    typedef btree_node<Params> node_type;
    typedef typename node_type::base_fields base_fields;
    typedef typename node_type::leaf_fields leaf_fields;
    typedef typename node_type::internal_fields internal_fields;
    typedef typename node_type::root_fields root_fields;
    typedef typename Params::is_key_compare_to is_key_compare_to;

    friend struct btree_internal_locate_plain_compare;
    friend struct btree_internal_locate_compare_to;
    typedef std::conditional_t<is_key_compare_to::value,
                               btree_internal_locate_compare_to,
                               btree_internal_locate_plain_compare>
        internal_locate_type;

    enum
    {
        kNodeValues = node_type::kNodeValues,
        kMinNodeValues = kNodeValues / 2,
        kValueSize = node_type::kValueSize,
        kExactMatch = node_type::kExactMatch,
        kMatchMask = node_type::kMatchMask,
    };

    // A helper class to get the empty base class optimization for 0-size
    // allocators. Base is internal_allocator_type.
    // (e.g. empty_base_handle<internal_allocator_type, node_type*>). If Base is
    // 0-size, the compiler doesn't have to reserve any space for it and
    // sizeof(empty_base_handle) will simply be sizeof(Data). Google [empty base
    // class optimization] for more details.
    template <typename Base, typename Data>
    struct empty_base_handle : public Base
    {
        empty_base_handle(const Base &b, const Data &d);
        Data data;
    };

    struct node_stats
    {
        node_stats(ssize_t l, ssize_t i);

        node_stats &operator+=(const node_stats &x);

        ssize_t leaf_nodes;
        ssize_t internal_nodes;
    };

public:
    typedef Params params_type;
    typedef typename Params::key_type key_type;
    typedef typename Params::data_type data_type;
    typedef typename Params::mapped_type mapped_type;
    typedef typename Params::value_type value_type;
    typedef typename Params::key_compare key_compare;
    typedef typename Params::pointer pointer;
    typedef typename Params::const_pointer const_pointer;
    typedef typename Params::reference reference;
    typedef typename Params::const_reference const_reference;
    typedef typename Params::size_type size_type;
    typedef typename Params::difference_type difference_type;
    typedef btree_iterator<node_type, reference, pointer> iterator;
    typedef typename iterator::const_iterator const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;

    typedef typename Params::allocator_type allocator_type;
    typedef typename Params::allocator_traits allocator_traits;
    typedef typename Params::internal_allocator_type internal_allocator_type;
    typedef typename Params::internal_allocator_traits internal_allocator_traits;

public:
    // Default constructor.
    btree(const key_compare &comp, const allocator_type &alloc);

    // Copy constructor.
    btree(const self_type &x);

    // Destructor.
    ~btree();

    // Iterator routines.
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    // Finds the first element whose key is not less than key.
    iterator lower_bound(const key_type &key);
    const_iterator lower_bound(const key_type &key) const;

    // Finds the first element whose key is greater than key.
    iterator upper_bound(const key_type &key);
    const_iterator upper_bound(const key_type &key) const;

    // Finds the range of values which compare equal to key. The first member of
    // the returned pair is equal to lower_bound(key). The second member pair of
    // the pair is equal to upper_bound(key).
    std::pair<iterator, iterator> equal_range(const key_type &key);

    std::pair<const_iterator, const_iterator> equal_range(const key_type &key) const;

    // Inserts a value into the btree only if it does not already exist. The
    // boolean return value indicates whether insertion succeeded or failed.
    template <typename... Args>
    std::pair<iterator, bool> emplace_unique_key_args(const key_type &key, Args &&... args);

    template <typename P>
    std::pair<iterator, bool> emplace_unique(P &&x);

    template <typename First, typename Second>
    typename std::enable_if<
        btree_can_extract_map_key<First, key_type, value_type>::value,
        std::pair<iterator, bool>>::type
    emplace_unique(First &&f, Second &&s);

    // Inserts a value into the btree only if it does not already exist. The
    // boolean return value indicates whether insertion succeeded or failed.
    template <typename... Args>
    std::pair<iterator, bool> emplace_unique(Args &&... args);

    template <class P>
    std::pair<iterator, bool>
    emplace_unique_extract_key(P &&x, btree_extract_key_fail_tag);

    template <class P>
    std::pair<iterator, bool>
    emplace_unique_extract_key(P &&x, btree_extract_key_self_tag);

    template <class P>
    std::pair<iterator, bool>
    emplace_unique_extract_key(P &&x, btree_extract_key_first_tag);

    // Insert with hint. Check to see if the value should be placed immediately
    // before position in the tree. If it does, then the insertion will take
    // amortized constant time. If not, the insertion will take amortized
    // logarithmic time as if a call to emplace_unique(v) were made.
    template <typename... Args>
    inline iterator emplace_hint_unique_key_args(const_iterator hint, const key_type &key, Args &&... args);

    template <typename P>
    std::pair<iterator, bool> emplace_hint_unique(const_iterator hint, P &&x);

    template <typename First, typename Second>
    typename std::enable_if<
        btree_can_extract_map_key<First, key_type, value_type>::value,
        iterator>::type
    emplace_hint_unique(const_iterator hint, First &&f, Second &&s);

    // Inserts a value into the btree only if it does not already exist. The
    // boolean return value indicates whether insertion succeeded or failed.
    template <typename... Args>
    iterator emplace_hint_unique(const_iterator hint, Args &&... args);

    template <class P>
    iterator
    emplace_hint_unique_extract_key(const_iterator hint, P &&x, btree_extract_key_fail_tag);

    template <class P>
    iterator
    emplace_hint_unique_extract_key(const_iterator hint, P &&x, btree_extract_key_self_tag);

    template <class P>
    iterator
    emplace_hint_unique_extract_key(const_iterator hint, P &&x, btree_extract_key_first_tag);

    std::pair<iterator, bool> insert_unique(const value_type &v);
    std::pair<iterator, bool> insert_unique(value_type &&v);
    iterator insert_unique(const_iterator hint, const value_type &v);
    iterator insert_unique(const_iterator hint, value_type &&v);
    template <typename P, typename = typename std::enable_if<
                              !std::is_same<
                                  typename std::remove_const<typename std::remove_reference<P>::type>::type,
                                  value_type>::value>::type>
    std::pair<iterator, bool> insert_unique(P &&x);
    template <typename P, typename = typename std::enable_if<
                              !std::is_same<
                                  typename std::remove_const<typename std::remove_reference<P>::type>::type,
                                  value_type>::value>::type>
    iterator insert_unique(const_iterator hint, P &&x);

    // Inserts a value into the btree.
    template <typename... Args>
    iterator emplace_multi_key_args(const key_type &key, Args &&... args);

    // Inserts a value into the btree.
    template <typename... Args>
    iterator emplace_multi(Args &&... args);

    // Insert with hint. Check to see if the value should be placed immediately
    // before hint position in the tree. If it does, then the insertion will take
    // amortized constant time. If not, the insertion will take amortized
    // logarithmic time as if a call to emplace_multi(v) were made.
    template <typename... Args>
    iterator emplace_hint_multi_key_args(const_iterator hint, const key_type &key, Args &&... args);

    // Inserts a value into the btree.
    template <typename... Args>
    iterator emplace_hint_multi(const_iterator hint, Args &&... args);

    iterator insert_multi(const value_type &v);
    iterator insert_multi(value_type &&v);
    iterator insert_multi(const_iterator hint, const value_type &v);
    iterator insert_multi(const_iterator hint, value_type &&v);
    template <typename P, typename = typename std::enable_if<
                              !std::is_same<
                                  typename std::remove_const<typename std::remove_reference<P>::type>::type,
                                  value_type>::value>::type>
    iterator insert_multi(P &&x);
    template <typename P, typename = typename std::enable_if<
                              !std::is_same<
                                  typename std::remove_const<typename std::remove_reference<P>::type>::type,
                                  value_type>::value>::type>
    iterator insert_multi(const_iterator hint, P &&x);

    void assign(const self_type &x);

    // Erase the specified iterator from the btree. The iterator must be valid
    // (i.e. not equal to end()).  Return an iterator pointing to the node after
    // the one that was erased (or end() if none exists).
    iterator erase(const_iterator iter);

    // Erases range. Returns the number of keys erased.
    int erase(const_iterator begin, const_iterator end);

    // Erases the specified key from the btree. Returns 1 if an element was
    // erased and 0 otherwise.
    int erase_unique(const key_type &key);

    // Erases all of the entries matching the specified key from the
    // btree. Returns the number of elements erased.
    int erase_multi(const key_type &key);

    // Finds the iterator corresponding to a key or returns end() if the key is
    // not present.
    iterator find_unique(const key_type &key);
    const_iterator find_unique(const key_type &key) const;
    iterator find_multi(const key_type &key);
    const_iterator find_multi(const key_type &key) const;

    // Returns a count of the number of times the key appears in the btree.
    size_type count_unique(const key_type &key) const;
    // Returns a count of the number of times the key appears in the btree.
    size_type count_multi(const key_type &key) const;

    // Clear the btree, deleting all of the values it contains.
    void clear();

    // Swap the contents of* this and x.
    void swap(self_type &x);

    // Assign the contents of x to* this.
    self_type &operator=(const self_type &x);
    key_compare &__key_comp();
    const key_compare &key_comp() const;
    bool compare_keys(const key_type &x, const key_type &y) const;

    // Dump the btree to the specified ostream. Requires that operator<< is
    // defined for Key and Value.
    void dump(std::ostream &os) const;

    // Verifies the structure of the btree.
    void verify() const;

    // Size routines. Note that empty() is slightly faster than doing size()==0.
    size_type size() const;

    size_type max_size() const;

    bool empty() const;

    // The height of the btree. An empty tree will have height 0.
    size_type height() const;

    // The number of internal, leaf and total nodes used by the btree.
    size_type leaf_nodes() const;
    size_type internal_nodes() const;
    size_type nodes() const;

    // The total number of bytes used by the btree.
    size_type bytes_used() const;

    // The average number of bytes used per value stored in the btree.
    static double average_bytes_per_value();

    // The fullness of the btree. Computed as the number of elements in the btree
    // divided by the maximum number of elements a tree with the current number
    // of nodes could hold. A value of 1 indicates perfect space
    // utilization. Smaller values indicate space wastage.
    double fullness() const;
    // The overhead of the btree structure in bytes per node. Computed as the
    // total number of bytes used by the btree minus the number of bytes used for
    // storing elements divided by the number of elements.
    double overhead() const;

private:
    // Internal accessor routines.
    node_type *root();
    const node_type *root() const;
    node_type *&__root();

    // The rightmost node is stored in the root node.
    node_type *rightmost();
    const node_type *rightmost() const;
    node_type *&__rightmost();

    // The leftmost node is stored as the parent of the root node.
    node_type *leftmost();
    const node_type *leftmost() const;

    // The size of the tree is stored in the root node.
    size_type &__size();

    // Allocator routines.
    internal_allocator_type &__internal_allocator() noexcept;
    const internal_allocator_type &internal_allocator() const noexcept;

    allocator_type allocator() const noexcept;

    // Node creation/deletion routines.
    node_type *new_internal_node(node_type *parent);
    node_type *new_internal_root_node();
    node_type *new_leaf_node(node_type *parent);
    node_type *new_leaf_root_node(int max_count);
    void delete_internal_node(node_type *node);
    void delete_internal_root_node();
    void delete_leaf_node(node_type *node);

    // Rebalances or splits the node iter points to.
    void rebalance_or_split(iterator &iter);

    // Merges the values of left, right and the delimiting key on their parent
    // onto left, removing the delimiting key and deleting right.
    void merge_nodes(node_type *left, node_type *right);

    // Tries to merge node with its left or right sibling, and failing that,
    // rebalance with its left or right sibling. Returns true if a merge
    // occurred, at which point it is no longer valid to access node. Returns
    // false if no merging took place.
    bool try_merge_or_rebalance(const_iterator &iter);

    // Tries to shrink the height of the tree by 1.
    void try_shrink();

    iterator internal_end(const_iterator iter);
    const_iterator internal_end(const_iterator iter) const;

    // Inserts a value into the btree immediately before iter. Requires that
    // key(v) <= iter.key() and (--iter).key() <= key(v).
    template <typename... Args>
    inline iterator internal_emplace(const_iterator hint, Args &&... args);

    // Returns an iterator pointing to the first value >= the value "iter" is
    // pointing at. Note that "iter" might be pointing to an invalid location as
    // iter.position == iter.node->count(). This routine simply moves iter up in
    // the tree to a valid location.
    template <typename IterType>
    static inline IterType internal_last(IterType iter);

    // Returns an iterator pointing to the leaf position at which key would
    // reside in the tree. We provide 2 versions of internal_locate. The first
    // version (internal_locate_plain_compare) always returns 0 for the second
    // field of the pair. The second version (internal_locate_compare_to) is for
    // the key-compare-to specialization and returns either kExactMatch (if the
    // key was found in the tree) or -kExactMatch (if it wasn't) in the second
    // field of the pair. The compare_to specialization allows the caller to
    // avoid a subsequent comparison to determine if an exact match was made,
    // speeding up string keys.
    template <typename IterType>
    inline std::pair<IterType, int> internal_locate(const key_type &key, IterType iter) const;
    template <typename IterType>
    inline std::pair<IterType, int> internal_locate_plain_compare(const key_type &key, IterType iter) const;

    template <typename IterType>
    inline std::pair<IterType, int> internal_locate_compare_to(const key_type &key, IterType iter) const;

    // Internal routine which implements lower_bound().
    template <typename IterType>
    IterType internal_lower_bound(const key_type &key, IterType iter) const;

    // Internal routine which implements upper_bound().
    template <typename IterType>
    IterType internal_upper_bound(const key_type &key, IterType iter) const;

    // Internal routine which implements find_unique().
    template <typename IterType>
    IterType internal_find_unique(const key_type &key, IterType iter) const;

    // Internal routine which implements find_multi().
    template <typename IterType>
    IterType internal_find_multi(const key_type &key, IterType iter) const;

    // Deletes a node and all of its children.
    void internal_clear(node_type *node);

    // Dumps a node and all of its children to the specified ostream.
    void internal_dump(std::ostream &os, const node_type *node, int level) const;

    // Verifies the tree structure of node.
    int internal_verify(const node_type *node, const key_type *lo, const key_type *hi) const;

    node_stats internal_stats(const node_type *node) const;

private:
    empty_base_handle<internal_allocator_type, node_type *> root_;

private:
    // A never instantiated helper function that returns big_ if we have a
    // key-compare-to functor or if R is bool and small_ otherwise.
    template <typename R>
    static std::conditional_t<
        std::conditional_t<is_key_compare_to::value,
                           std::is_same<R, int>,
                           std::is_same<R, bool>>::value,
        big_,
        small_>
        key_compare_checker(R);

    // A never instantiated helper function that returns the key comparison
    // functor.
    static key_compare key_compare_helper();
};

#pragma region // container

// A common base class for btree::set, map, btree_multiset and
// btree_multimap.
template <typename Tree>
class btree_container
{
    typedef btree_container<Tree> self_type;

public:
    typedef typename Tree::params_type params_type;
    typedef typename Tree::key_type key_type;
    typedef typename Tree::value_type value_type;
    typedef typename Tree::key_compare key_compare;
    typedef typename Tree::allocator_type allocator_type;
    typedef typename Tree::pointer pointer;
    typedef typename Tree::const_pointer const_pointer;
    typedef typename Tree::reference reference;
    typedef typename Tree::const_reference const_reference;
    typedef typename Tree::size_type size_type;
    typedef typename Tree::difference_type difference_type;
    typedef typename Tree::iterator iterator;
    typedef typename Tree::const_iterator const_iterator;
    typedef typename Tree::reverse_iterator reverse_iterator;
    typedef typename Tree::const_reverse_iterator const_reverse_iterator;

public:
    // Default constructor.
    btree_container(const key_compare &comp, const allocator_type &alloc);

    // Copy constructor.
    btree_container(const self_type &x);

    // Iterator routines.
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    // Lookup routines.
    iterator lower_bound(const key_type &key);
    const_iterator lower_bound(const key_type &key) const;
    iterator upper_bound(const key_type &key);
    const_iterator upper_bound(const key_type &key) const;
    std::pair<iterator, iterator> equal_range(const key_type &key);
    std::pair<const_iterator, const_iterator> equal_range(const key_type &key) const;

    allocator_type get_allocator() const noexcept;

    // Utility routines.
    void clear();
    void swap(self_type &x);
    void dump(std::ostream &os) const;
    void verify() const;

    // Size routines.
    size_type size() const;
    size_type max_size() const;
    bool empty() const;

    size_type height() const;
    size_type internal_nodes() const;
    size_type leaf_nodes() const;
    size_type nodes() const;
    size_type bytes_used() const;
    static double average_bytes_per_value();
    double fullness() const;
    double overhead() const;

    bool operator==(const self_type &x) const;

    bool operator!=(const self_type &other) const;

protected:
    Tree __tree;
};

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const btree_container<T> &b);

// A common base class for btree::map and btree::set.
template <typename Tree>
class btree_unique_container : public btree_container<Tree>
{
    typedef btree_unique_container<Tree> self_type;
    typedef btree_container<Tree> super_type;

public:
    typedef typename Tree::key_type key_type;
    typedef typename Tree::value_type value_type;
    typedef typename Tree::size_type size_type;
    typedef typename Tree::key_compare key_compare;
    typedef typename Tree::allocator_type allocator_type;
    typedef typename Tree::iterator iterator;
    typedef typename Tree::const_iterator const_iterator;

public:
    // Default constructor.
    btree_unique_container(const key_compare &comp = key_compare(),
                           const allocator_type &alloc = allocator_type());

    // Copy constructor.
    btree_unique_container(const self_type &x);

    // Range constructor.
    template <class InputIterator>
    btree_unique_container(InputIterator b, InputIterator e,
                           const key_compare &comp = key_compare(),
                           const allocator_type &alloc = allocator_type());

    // Lookup routines.
    iterator find(const key_type &key);
    const_iterator find(const key_type &key) const;
    size_type count(const key_type &key) const;
#if __cplusplus > 201703L
    bool contains(const key_type &key) const;
#endif

    // Insertion routines.
    std::pair<iterator, bool> insert(const value_type &x);
    template <typename P>
    std::pair<iterator, bool> insert(P &&x);
    std::pair<iterator, bool> insert(value_type &&x);
    iterator insert(const_iterator hint, const value_type &x);
    template <typename P>
    std::pair<iterator, bool> insert(const_iterator hint, P &&x);
    iterator insert(const_iterator hint, value_type &&x);
    void insert(std::initializer_list<value_type> il);
    template <typename InputIterator>
    void insert(InputIterator f, InputIterator l);

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args &&... args);

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args &&... args);

    // Deletion routines.
    int erase(const key_type &key);
    // Erase the specified iterator from the btree. The iterator must be valid
    // (i.e. not equal to end()).  Return an iterator pointing to the node after
    // the one that was erased (or end() if none exists).
    iterator erase(const iterator &iter);
    void erase(const iterator &first, const iterator &last);
};

// A common base class for btree::multimap and btree::multiset.
template <typename Tree>
class btree_multi_container : public btree_container<Tree>
{
    typedef btree_multi_container<Tree> self_type;
    typedef btree_container<Tree> super_type;

public:
    typedef typename Tree::key_type key_type;
    typedef typename Tree::value_type value_type;
    typedef typename Tree::size_type size_type;
    typedef typename Tree::key_compare key_compare;
    typedef typename Tree::allocator_type allocator_type;
    typedef typename Tree::iterator iterator;
    typedef typename Tree::const_iterator const_iterator;

public:
    // Default constructor.
    btree_multi_container(const key_compare &comp = key_compare(),
                          const allocator_type &alloc = allocator_type());

    // Copy constructor.
    btree_multi_container(const self_type &x);

    // Range constructor.
    template <class InputIterator>
    btree_multi_container(InputIterator b, InputIterator e,
                          const key_compare &comp = key_compare(),
                          const allocator_type &alloc = allocator_type());

    // Lookup routines.
    iterator find(const key_type &key);
    const_iterator find(const key_type &key) const;
    size_type count(const key_type &key) const;
#if __cplusplus > 201703L
    bool contains(const key_type &key) const;
#endif

    // Insertion routines.
    iterator insert(const value_type &x);
    template <typename P>
    iterator insert(P &&x);
    iterator insert(value_type &&x);
    iterator insert(const_iterator hint, const value_type &x);
    template <typename P>
    iterator insert(const_iterator hint, P &&x);
    iterator insert(const_iterator hint, value_type &&x);
    template <typename InputIterator>
    void insert(InputIterator f, InputIterator l);
    void insert(std::initializer_list<value_type> il);

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args &&... args);

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args &&... args);

    // Deletion routines.
    int erase(const key_type &key);

    // Erase the specified iterator from the btree. The iterator must be valid
    // (i.e. not equal to end()).  Return an iterator pointing to the node after
    // the one that was erased (or end() if none exists).
    iterator erase(const iterator &iter);
    void erase(const iterator &first, const iterator &last);
};

#pragma endregion

#endif // BTREE_BTREE_H__
