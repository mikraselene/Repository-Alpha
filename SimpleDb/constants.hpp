#ifndef SIMPLEDB_CONSTANTS_HPP_
#define SIMPLEDB_CONSTANTS_HPP_

#include <iostream>

namespace database
{
    constexpr uint32_t KEY_LENGTH = 64;
    constexpr uint32_t ROWS_PER_PAGE = 1024;
    constexpr uint32_t MAX_PAGES = 262144;

    constexpr uint32_t KEY_SIZE = KEY_LENGTH * sizeof(char);
    constexpr uint32_t POS_SIZE = sizeof(uint);
    constexpr uint32_t ROW_SIZE = KEY_SIZE + POS_SIZE + POS_SIZE;
    constexpr uint32_t PAGE_SIZE = ROW_SIZE * ROWS_PER_PAGE;
    constexpr uint32_t MAX_ROWS = ROWS_PER_PAGE * MAX_PAGES;
    constexpr uint32_t TABLE_SIZE = PAGE_SIZE * MAX_PAGES;

    constexpr uint32_t CELL_SIZE = 0;
    constexpr uint32_t MAX_CELLS = 0;

    constexpr off_t KEY_OFFSET = 0;
    constexpr off_t LPOS_OFFSET = KEY_OFFSET + KEY_SIZE;
    constexpr off_t RPOS_OFFSET = LPOS_OFFSET + POS_SIZE;

} // namespace database

namespace btree_node
{
    constexpr uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
    constexpr uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
    constexpr uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
    constexpr uint32_t COMMON_NODE_HEADER_SIZE =
        NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;
    constexpr uint32_t NUM_CELLS_SIZE = sizeof(uint32_t);
    constexpr uint32_t HEADER_SIZE = COMMON_NODE_HEADER_SIZE + NUM_CELLS_SIZE;
    constexpr uint32_t KEY_SIZE = 0; // TODO:
    constexpr uint32_t VALUE_SIZE = database::ROW_SIZE;
    constexpr uint32_t CELL_SIZE = KEY_SIZE + VALUE_SIZE;

    constexpr off_t NODE_TYPE_OFFSET = 0;
    constexpr off_t IS_ROOT_OFFSET = NODE_TYPE_OFFSET + NODE_TYPE_SIZE;
    constexpr off_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;
    constexpr off_t NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
    constexpr off_t KEY_OFFSET = 0;
    constexpr off_t VALUE_OFFSET = KEY_OFFSET + KEY_SIZE;
    constexpr uint32_t MAX_CELLS =
        (database::PAGE_SIZE - HEADER_SIZE) / CELL_SIZE;

} // namespace btree_node

#endif // SIMPLEDB_CONSTANTS_HPP_
