#include <iostream>
#include <vector>
using namespace std;

/*

column          size            offset
------------------------------------------------
key             64              0
left_pos        4               64
right_pos       4               68
total           72

*/

/*

1. Store rows in blocks of memory called pages
2. Each page stores as many rows as it can fit
3. Rows are serialized into a compact representation with each page
4. Pages are only allocated as needed
5. Keep a fixed-size array of pointers to pages

*/
const uint KEY_SIZE = 8 * sizeof(char);
const uint POS_SIZE = sizeof(uint);
const uint ROW_SIZE = KEY_SIZE + 2 * POS_SIZE;
const uint KEY_OFFSET = 0;
const uint LPOS_OFFSET = KEY_OFFSET + KEY_SIZE;
const uint RPOS_OFFSET = LPOS_OFFSET + POS_SIZE;

const uint ROWS_PER_PAGE = 128;
const uint PAGE_SIZE = ROW_SIZE * ROWS_PER_PAGE;
const uint MAX_PAGES = 100;
const uint MAX_ROWS = ROWS_PER_PAGE * MAX_PAGES;

class Pager
{
private:
    int file_descriptor;
    uint file_length;
    void *pages[MAX_PAGES];
};

class Row
{
public:
    Row() {}
    Row(string key, pair<uint, uint> pos)
    {
        key.resize(KEY_SIZE, ' ');
        strcpy(key_, key.c_str());
        left_pos_ = pos.first;
        right_pos_ = pos.second;
    }
    void serialize_to(void *to)
    {
        memcpy((char *)to + KEY_OFFSET, &key_, KEY_SIZE);
        memcpy((char *)to + LPOS_OFFSET, &left_pos_, POS_SIZE);
        memcpy((char *)to + RPOS_OFFSET, &right_pos_, POS_SIZE);
    }
    void deserialize_from(void *from)
    {
        memcpy(&key_, (char *)from + KEY_OFFSET, KEY_SIZE);
        memcpy(&left_pos_, (char *)from + LPOS_OFFSET, POS_SIZE);
        memcpy(&right_pos_, (char *)from + RPOS_OFFSET, POS_SIZE);
    }
    void print()
    {
        for (auto i : key_)
        {
            printf("%c", i);
        }
        printf(", %d, %d\n", left_pos_, right_pos_);
    }

private:
    char key_[KEY_SIZE];
    uint left_pos_;
    uint right_pos_;
};
/*
void serialize_row(Row *from, void *to)
{
    memcpy((char *)to + KEY_OFFSET, &(from->key), KEY_SIZE);
    memcpy((char *)to + LPOS_OFFSET, &(from->left_pos), POS_SIZE);
    memcpy((char *)to + RPOS_OFFSET, &(from->right_pos), POS_SIZE);
}
void deserialize_row(void *from, Row *to)
{
    memcpy(&(to->key), (char *)from + KEY_OFFSET, KEY_SIZE);
    memcpy(&(to->left_pos), (char *)from + LPOS_OFFSET, POS_SIZE);
    memcpy(&(to->right_pos), (char *)from + RPOS_OFFSET, POS_SIZE);
}
*/

class Table
{
public:
    Table() : num_of_rows(0), pages() {}
    auto row_slot(uint row_num) -> void *
    {
        uint page_num = row_num / ROWS_PER_PAGE;
        void *page = pages[page_num];
        if (page == nullptr)
        {
            page = pages[page_num] = malloc(PAGE_SIZE);
        }
        uint offset = (row_num % ROWS_PER_PAGE) * ROW_SIZE;
        return (char *)page + offset;
    }
    void execute_insert(Row row)
    {
        row.serialize_to(row_slot(num_of_rows));
        num_of_rows++;
    }
    void execute_select()
    {
        for (auto i = 0; i < num_of_rows; i++)
        {
            Row row;
            row.deserialize_from(row_slot(i));
            row.print();
        }
    }
    uint num_of_rows;
    void *pages[MAX_PAGES];
    Pager *pager;
};

int main()
{
    Table *table = new Table;
    Row row("keykeykde", {114, 514});
    table->execute_insert(row);
    table->execute_select();
}
