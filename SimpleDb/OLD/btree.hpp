#ifndef SIMPLEDB_BTREE_HPP_
#define SIMPLEDB_BTREE_HPP_
// Ｂ木「ビーツリークリーチャー」

#include <string>
#include <iostream>
#include "./cosmic_mind.h"
#include "constants.hpp"

enum class NodeType
{
    INTERNAL,
    LEAF,
    UNKNOWN,
};
using pointer = void *;
#define CAST_UINT(x) reinterpret_cast<uint32_t *>(x)
template <class T>
class Node
{
public:
    explicit Node(T *node_ptr) : node_ptr_(node_ptr) {}
    auto leaf_node_num_cells() -> uint32_t *
    {
        return reinterpret_cast<uint32_t *>(
            reinterpret_cast<char *>(node_ptr_) + btree_node::NUM_CELLS_OFFSET);
    }
    auto leaf_node_cell(uint32_t cell_num) -> pointer
    {
        return reinterpret_cast<char *>(node_ptr_) +
               btree_node::HEADER_SIZE + cell_num * btree_node::CELL_SIZE;
    }
    auto leaf_node_key(uint32_t cell_num) -> char *
    {
        return nullptr;
    }
    auto leaf_node_value(uint32_t cell_num) -> pointer
    {
        return reinterpret_cast<char *>(leaf_node_cell(cell_num)) +
               btree_node::KEY_SIZE;
    }
    void initialize() { *leaf_node_num_cells() = 0; } // WHY?

private:
    T *node_ptr_;
};

//

//

//

#endif // SIMPLEDB_BTREE_HPP_
