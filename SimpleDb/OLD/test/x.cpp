#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <vector>

using std::string;

const uint KEY_LENGTH = 8;
const uint ROWS_PER_PAGE = 1024;
const uint MAX_PAGES = 262144;

const uint KEY_SIZE = KEY_LENGTH * sizeof(char);
const uint POS_SIZE = sizeof(uint);
const uint ROW_SIZE = KEY_SIZE + POS_SIZE + POS_SIZE;
const uint KEY_OFFSET = 0;
const uint LPOS_OFFSET = KEY_OFFSET + KEY_SIZE;
const uint RPOS_OFFSET = LPOS_OFFSET + POS_SIZE;
const uint PAGE_SIZE = ROW_SIZE * ROWS_PER_PAGE;
const uint MAX_ROWS = ROWS_PER_PAGE * MAX_PAGES;
const uint TABLE_SIZE = PAGE_SIZE * MAX_PAGES;

using pointer = void *;

#define CAST(x) reinterpret_cast<char *>(x)

enum class TablePosition
{
    START,
    END,
    OTHER,
};

class Row
{
public:
    Row();
    Row(string key, int lpos, int rpos);
    void serialize_to(pointer to);
    void deserialize_from(pointer from);
    void print();

private:
    char key_[KEY_LENGTH];
    uint left_pos_;
    uint right_pos_;
};

class Pager
{
public:
    Pager();
    Pager(int file_descriptor, uint file_length);
    auto get_page(uint page_num) -> pointer;
    auto pages(uint page_num) -> pointer;
    void nullptrify(uint page_num);
    auto file_length() -> uint;
    auto file_descriptor() -> int;
    void flush(uint page_num, uint size);

private:
    uint num_of_pages_;
    int file_descriptor_;
    uint file_length_;
    pointer pages_[MAX_PAGES];
};

class Table
{
public:
    Table();
    Table(Pager *pager, uint num_of_rows);
    auto row_slot(uint row_num) -> pointer;
    void insert(Row row);
    void select();
    auto pager() -> Pager *;
    auto num_of_rows() -> uint;

private:
    uint num_of_rows_;
    Pager *pager_;
};

class Cursor
{
public:
    Cursor(Table *table, TablePosition pos);
    auto row_num() -> uint;
    auto table() -> Table *;
    auto ptr_value() -> pointer;
    void increment();
    bool table_end();
    auto operator++() -> Cursor &;
    auto operator++(int) -> Cursor;

private:
    Table *table_;
    uint row_num_;
    bool table_end_;
};

class Database
{
public:
    Database();
    void dbopen(const char *filename);
    void dbclose();
    auto table() -> Table *;

private:
    Table *table_;
};

#pragma region // Row Implementations
Row::Row()
{
}
Row::Row(string key, int lpos, int rpos)
{
    key.resize(KEY_LENGTH, ' ');
    snprintf(key_, KEY_LENGTH, "%s", key.c_str());
    left_pos_ = lpos;
    right_pos_ = rpos;
}
void Row::serialize_to(pointer to)
{
    memcpy(CAST(to) + KEY_OFFSET, &key_, KEY_SIZE);
    memcpy(CAST(to) + LPOS_OFFSET, &left_pos_, POS_SIZE);
    memcpy(CAST(to) + RPOS_OFFSET, &right_pos_, POS_SIZE);
}
void Row::deserialize_from(pointer from)
{
    memcpy(&key_, CAST(from) + KEY_OFFSET, KEY_SIZE);
    memcpy(&left_pos_, CAST(from) + LPOS_OFFSET, POS_SIZE);
    memcpy(&right_pos_, CAST(from) + RPOS_OFFSET, POS_SIZE);
}
void Row::print()
{
    printf("%s", key_);
    printf(", %d, %d\n", left_pos_, right_pos_);
}
#pragma endregion

#pragma region // Pager Implementations
Pager::Pager() : file_descriptor_(0), file_length_(0), pages_()
{
}
Pager::Pager(int file_descriptor, uint file_length)
    : file_descriptor_(file_descriptor),
      file_length_(file_length),
      pages_() {}
auto Pager::get_page(uint page_num) -> pointer
{
    if (page_num > MAX_PAGES)
    {
        throw "dd";
    }
    if (pages_[page_num] == nullptr)
    {
        auto page = malloc(PAGE_SIZE);
        auto num_pages = file_length_ / PAGE_SIZE;
        if (file_length_ % PAGE_SIZE != 0)
        {
            num_of_pages_++;
        }
        if (page_num < num_of_pages_)
        {
            lseek(file_descriptor_, page_num * PAGE_SIZE, SEEK_SET);
            auto r = read(file_descriptor_, page, PAGE_SIZE);
        }
        pages_[page_num] = page;
    }
    return pages_[page_num];
}
auto Pager::pages(uint page_num) -> pointer { return pages_[page_num]; }
void Pager::nullptrify(uint page_num) { pages_[page_num] = nullptr; }
auto Pager::file_length() -> uint { return file_length_; }
auto Pager::file_descriptor() -> int { return file_descriptor_; }
void Pager::flush(uint page_num, uint size)
{
    if (pages_[page_num] == nullptr)
    {
        exit(1);
    }
    auto offset = lseek(file_descriptor_, page_num * PAGE_SIZE, SEEK_SET);
    auto w = write(file_descriptor_, pages_[page_num], size);
}
#pragma endregion

#pragma region // Table Implementations
Table::Table() : num_of_rows_(0), pager_(new Pager(0, 0))
{
}
Table::Table(Pager *pager, uint num_of_rows)
    : pager_(pager), num_of_rows_(num_of_rows) {}
auto Table::row_slot(uint row_num) -> pointer
{
    uint page_num = row_num / ROWS_PER_PAGE;
    pointer page = pager_->get_page(page_num);
    uint offset = (row_num % ROWS_PER_PAGE) * ROW_SIZE;
    return CAST(page) + offset;
}
void Table::insert(Row row)
{
    Cursor cursor(this, TablePosition::END);
    row.serialize_to(cursor.ptr_value());
    num_of_rows_++;
}
void Table::select()
{
    Cursor cursor(this, TablePosition::START);
    Row row;
    while (!cursor.table_end())
    {
        row.deserialize_from(cursor.ptr_value());
        row.print();
        cursor++;
    }
}
auto Table::pager() -> Pager * { return pager_; }
auto Table::num_of_rows() -> uint { return num_of_rows_; }
#pragma endregion

#pragma region // Cursor Implementations
Cursor::Cursor(Table *table, TablePosition pos)
    : table_(table),
      row_num_(pos == TablePosition::END ? table->num_of_rows() : 0),
      table_end_(pos == TablePosition::START
                     ? table->num_of_rows() == 0
                     : true)
{
}
auto Cursor::row_num() -> uint { return row_num_; }
auto Cursor::table() -> Table * { return table_; }
auto Cursor::ptr_value() -> pointer
{
    uint page_num = row_num_ / ROWS_PER_PAGE;
    pointer page = table_->pager()->get_page(page_num);
    uint offset = (row_num_ % ROWS_PER_PAGE) * ROW_SIZE;
    return CAST(page) + offset;
}
void Cursor::increment()
{
    row_num_++;
    if (row_num_ >= table_->num_of_rows())
    {
        table_end_ = true;
    }
}
bool Cursor::table_end() { return table_end_; }
auto Cursor::operator++() -> Cursor &
{
    row_num_++;
    if (row_num_ >= table_->num_of_rows())
    {
        table_end_ = true;
    }
    return *this;
}
auto Cursor::operator++(int) -> Cursor
{
    return ++(*this);
}

#pragma endregion

#pragma region // Database Implementations
Database::Database() : table_(nullptr)
{
}
void Database::dbopen(const char *filename)
{
    auto file_descriptor = // TODO:
        open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    auto file_length = lseek(file_descriptor, 0, SEEK_END);
    auto pager = new Pager(file_descriptor, file_length);
    auto num_of_rows = pager->file_length() / ROW_SIZE;
    table_ = new Table(pager, num_of_rows);
}
void Database::dbclose()
{
    auto pager = table_->pager();
    auto num_of_full_pages = table_->num_of_rows() / ROWS_PER_PAGE;
    for (auto i = 0; i < num_of_full_pages; i++)
    {
        if (pager->pages(i) == nullptr)
        {
            continue;
        }
        pager->flush(i, PAGE_SIZE);
        free(pager->pages(i));
        pager->nullptrify(i);
    }
    auto num_of_additional_rows = table_->num_of_rows() % ROWS_PER_PAGE;
    if (num_of_additional_rows > 0)
    {
        auto page_num = num_of_full_pages;
        if (pager->pages(page_num) != nullptr)
        {
            pager->flush(page_num, num_of_additional_rows * ROW_SIZE);
            free(pager->pages(page_num));
            pager->nullptrify(page_num);
        }
    }
    int res = close(pager->file_descriptor());
    delete pager;
    delete table_;
    // TODO:
}
auto Database::table() -> Table * { return table_; }
#pragma endregion

int main()
{
    Database sample;
    sample.dbopen("y.db");
    sample.table()->insert(Row("whelloworld", 33, 514));
    sample.table()->select();
    sample.dbclose();
}