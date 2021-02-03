#ifndef SIMPLEDB_CONSTANTS_HPP_
#define SIMPLEDB_CONSTANTS_HPP_

#include <iostream>

namespace database
{
    const uint32_t KEY_LENGTH = 8;
    const uint32_t ROWS_PER_PAGE = 1024;
    const uint32_t MAX_PAGES = 262144;

    const uint32_t KEY_SIZE = KEY_LENGTH * sizeof(char);
    const uint32_t POS_SIZE = sizeof(uint);
    const uint32_t ROW_SIZE = KEY_SIZE + POS_SIZE + POS_SIZE;
    const uint32_t PAGE_SIZE = ROW_SIZE * ROWS_PER_PAGE;
    const uint32_t MAX_ROWS = ROWS_PER_PAGE * MAX_PAGES;
    const uint32_t TABLE_SIZE = PAGE_SIZE * MAX_PAGES;

    const off_t KEY_OFFSET = 0;
    const off_t LPOS_OFFSET = KEY_OFFSET + KEY_SIZE;
    const off_t RPOS_OFFSET = LPOS_OFFSET + POS_SIZE;
} // namespace database

namespace btree_node
{
    const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
    const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
    const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
    const uint32_t COMMON_NODE_HEADER_SIZE =
        NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;
    const uint32_t NUM_CELLS_SIZE = sizeof(uint32_t);
    const uint32_t HEADER_SIZE = COMMON_NODE_HEADER_SIZE + NUM_CELLS_SIZE;
    const uint32_t KEY_SIZE = 0; // TODO:
    const uint32_t VALUE_SIZE = database::ROW_SIZE;
    const uint32_t CELL_SIZE = KEY_SIZE + VALUE_SIZE;

    const off_t NODE_TYPE_OFFSET = 0;
    const off_t IS_ROOT_OFFSET = NODE_TYPE_OFFSET + NODE_TYPE_SIZE;
    const off_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;
    const off_t NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
    const off_t KEY_OFFSET = 0;
    const off_t VALUE_OFFSET = KEY_OFFSET + KEY_SIZE;
    const uint32_t MAX_CELLS = (database::PAGE_SIZE - HEADER_SIZE) / CELL_SIZE;
} // namespace btree_node

#endif // SIMPLEDB_CONSTANTS_HPP_
