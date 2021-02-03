#ifndef SIMPLEDB_BTREE_HPP_
#define SIMPLEDB_BTREE_HPP_
// Ｂ木「ビーツリークリーチャー」

#include <iostream>
#include "./cosmic_mind.h"
#include "database.hpp"
#include "constants.hpp"

enum class NodeType
{
    INTERNAL,
    LEAF,
    UNKNOWN,
};

#define CAST_UINT(x) reinterpret_cast<uint32_t *>(x)
class Node
{
public:
    auto leaf_node_num_cells() -> uint32_t *
    {
        return CAST_UINT(CAST(node_ptr) + btree_node::NODE_TYPE_OFFSET);
    }
    auto leaf_node_cell(uint32_t cell_num) -> pointer
    {
        return CAST(node_ptr) +
               btree_node::HEADER_SIZE + cell_num * btree_node::CELL_SIZE;
    }
    auto leaf_node_key(uint32_t cell_num) -> pointer
    {
        return leaf_node_cell(cell_num);
    }
    auto leaf_node_value(uint32_t cell_num) -> pointer
    {
        return CAST(leaf_node_cell(cell_num)) + btree_node::KEY_SIZE;
    }
    void initialize() { *leaf_node_num_cells() = 0; } // WHY?

private:
    pointer node_ptr;
};

//

//

//

#endif // SIMPLEDB_BTREE_HPP_
