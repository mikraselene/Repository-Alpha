#ifndef SIMPLEDB_CODE_DATABASE_HPP_
#define SIMPLEDB_CODE_DATABASE_HPP_

#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <vector>
#include <string>

#include "constants.hpp"

using std::string;
using pointer = void *;

enum class TablePosition
{
    START,
    END,
    OTHER,
};

// Row 是包含 key-value 对的一行.
class Row
{
public:
    Row();
    Row(string key, int32_t lpos, int32_t rpos);
    // 把给定的一行序列化到 to 指向的内存中.
    void serialize_to(const pointer to) const;
    // 从 from 指向的内存中解序列化到给定的一行.
    void deserialize_from(const pointer from);
    // 在终端打印一行.
    void print() const;

    auto key() const -> string;
    auto left_pos() const -> uint32_t;
    auto right_pos() const -> uint32_t;

private:
    char key_[database::KEY_LENGTH]; // 字符串键
    int32_t left_pos_;               // xml 文件中的左位置
    int32_t right_pos_;              // xml 文件中的右位置 (XXX: 可以改成长度?)
};

// Pager 用于管理 Table 中的不同页.
class Pager
{
public:
    Pager();
    Pager(int file_descriptor, int32_t file_length, int32_t num_of_pages);
    // 获得 page_num 指向的页, 如果没有则新建一页.
    auto get_page(const int32_t &page_num) -> pointer;
    // 把 page_num 指向的页置为空指针.
    void nullptrify(const int32_t &page_num);
    // 把 page_num 指向的页写入文件.
    void flush(const int32_t &page_num, const int32_t &size) const;

    auto num_of_pages() const -> int32_t;
    auto file_descriptor() const -> int;
    auto file_length() const -> int32_t;
    auto pages(const int32_t &page_num) const -> pointer;

private:
    int32_t num_of_pages_;               // 总页数
    int file_descriptor_;                // 标示当前打开的文件
    int32_t file_length_;                // 文件长度
    pointer pages_[database::MAX_PAGES]; // 页
};

// Table 是存放数据的表本身.
class Table
{
public:
    Table();
    Table(Pager *pager, int32_t num_of_rows);
    // 读取给定 row_num 指向的行的位置.
    auto row_slot(const int32_t &row_num) const -> pointer;
    // 在表中插入一行.
    void insert(Row row);
    // 读取表中的所有行.
    void select();

    auto num_of_rows() const -> int32_t;
    auto pager() const -> Pager *;

private:
    int32_t num_of_rows_; // Table 中的总 Row 数.
    Pager *pager_;        // 页管理 Pager.
};

// Cursor 指明了 Table 中的一个位置.
class Cursor
{
public:
    Cursor(Table *table, TablePosition pos);
    // 当前 Cursor 的实际指针值.
    auto ptr_value() const -> pointer;
    // 前置自增运算符, 自增后 Cursor 指向下一条 Row.
    auto operator++() -> Cursor &;
    // 后置自增运算符, 自增后 Cursor 指向下一条 Row.
    auto operator++(int) -> Cursor;

    auto table() const -> Table *;
    auto row_num() const -> int32_t;
    bool table_end() const;

private:
    Table *table_;    // Cursor 所在的 Table
    int32_t row_num_; // Cursor 指向的 Row
    bool table_end_;  // 是否在 Table 尾部
};

// 数据库表层.
class Database
{
public:
    Database();
    // 打开一个数据库.
    void dbopen(const char *filename);
    // 关闭一个数据库. TODO: 多表数据库?
    void dbclose() const;

    auto table() const -> Table *;
    auto dbname() const -> string;
    bool is_open() const;

private:
    Table *table_;
    string dbname_;
    bool is_open_;
};

#pragma region // Row Implementations

Row::Row() : key_(), left_pos_(0), right_pos_(0)
{
}
Row::Row(string key, int32_t lpos, int32_t rpos)
    : left_pos_(lpos), right_pos_(rpos)
{
    assert(lpos >= 0);
    assert(rpos >= 0);
    key.resize(database::KEY_LENGTH, ' ');
    snprintf(key_, database::KEY_LENGTH, "%s", key.c_str());
}
void Row::serialize_to(const pointer to) const
{
    memcpy(reinterpret_cast<char *>(to) + database::KEY_OFFSET,
           &key_, database::KEY_SIZE);
    memcpy(reinterpret_cast<char *>(to) + database::LPOS_OFFSET,
           &left_pos_, database::POS_SIZE);
    memcpy(reinterpret_cast<char *>(to) + database::RPOS_OFFSET,
           &right_pos_, database::POS_SIZE);
}
void Row::deserialize_from(const pointer from)
{
    memcpy(&key_, reinterpret_cast<char *>(from) + database::KEY_OFFSET,
           database::KEY_SIZE);
    memcpy(&left_pos_, reinterpret_cast<char *>(from) + database::LPOS_OFFSET,
           database::POS_SIZE);
    memcpy(&right_pos_, reinterpret_cast<char *>(from) + database::RPOS_OFFSET,
           database::POS_SIZE);
}
void Row::print() const { printf("%s, %u, %u\n", key_, left_pos_, right_pos_); }

auto Row::key() const -> string { return key_; }
auto Row::left_pos() const -> uint32_t { return left_pos_; }
auto Row::right_pos() const -> uint32_t { return right_pos_; }

#pragma endregion

#pragma region // Pager Implementations

Pager::Pager() : file_descriptor_(0), file_length_(0), pages_()
{
}
Pager::Pager(int file_descriptor, int32_t file_length, int32_t num_of_pages)
    : num_of_pages_(num_of_pages),
      file_descriptor_(file_descriptor),
      file_length_(file_length),
      pages_()
{
    assert(num_of_pages >= 0);
    assert(file_length >= 0);
}
auto Pager::get_page(const int32_t &page_num) -> pointer
{
    assert(page_num >= 0);
    assert(page_num <= database::MAX_PAGES);
    if (pages_[page_num] == nullptr) // 若无给定的页, 则新建一页.
    {
        auto page = malloc(database::PAGE_SIZE);
        auto num_pages = file_length_ / database::PAGE_SIZE;
        assert(num_pages >= 0);
        if (file_length_ % database::PAGE_SIZE != 0)
        {
            num_of_pages_++;
        }
        if (page_num < num_of_pages_)
        {
            lseek(file_descriptor_, page_num * database::PAGE_SIZE, SEEK_SET);
            auto r = read(file_descriptor_, page, database::PAGE_SIZE);
            assert(r != -1);
        }
        pages_[page_num] = page;
        if (page_num >= num_of_pages_)
        {
            num_of_pages_ = page_num + 1;
        }
    }
    return pages_[page_num];
}
void Pager::nullptrify(const int32_t &page_num)
{
    assert(page_num >= 0);
    pages_[page_num] = nullptr;
}
void Pager::flush(const int32_t &page_num, const int32_t &size) const
{
    assert(page_num >= 0);
    assert(size >= 0);
    assert(pages_[page_num] != nullptr);
    auto offset =
        lseek(file_descriptor_, page_num * database::PAGE_SIZE, SEEK_SET);
    assert(offset != -1);
    auto w = write(file_descriptor_, pages_[page_num], size);
    assert(w != -1);
}

auto Pager::num_of_pages() const -> int32_t { return num_of_pages_; }
auto Pager::file_descriptor() const -> int { return file_descriptor_; }
auto Pager::file_length() const -> int32_t { return file_length_; }
auto Pager::pages(const int32_t &page_num) const
    -> pointer { return pages_[page_num]; }

#pragma endregion

#pragma region // Table Implementations

Table::Table() : num_of_rows_(0), pager_(new Pager)
{
}
Table::Table(Pager *pager, int32_t num_of_rows)
    : num_of_rows_(num_of_rows), pager_(pager) { assert(num_of_rows >= 0); }
auto Table::row_slot(const int32_t &row_num) const -> pointer
{
    assert(row_num >= 0);
    auto page_num = row_num / database::ROWS_PER_PAGE;
    auto page = pager_->get_page(page_num);
    auto offset = (row_num % database::ROWS_PER_PAGE) * database::ROW_SIZE;
    return reinterpret_cast<char *>(page) + offset;
}
void Table::insert(Row row)
{
    Cursor cursor(this, TablePosition::END); // 在 Table 尾部插入.
    row.serialize_to(cursor.ptr_value());
    num_of_rows_++;
}
void Table::select()
{
    Cursor cursor(this, TablePosition::START); // 从 Table 头部开始读取.
    Row row;
    while (!cursor.table_end())
    {
        row.deserialize_from(cursor.ptr_value());
        row.print();
        cursor++;
    }
}

auto Table::num_of_rows() const -> int32_t { return num_of_rows_; }
auto Table::pager() const -> Pager * { return pager_; }

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
auto Cursor::ptr_value() const -> pointer
{
    auto page_num = row_num_ / database::ROWS_PER_PAGE;
    auto page = table_->pager()->get_page(page_num);
    auto offset = (row_num_ % database::ROWS_PER_PAGE) * database::ROW_SIZE;
    return reinterpret_cast<char *>(page) + offset;
}
auto Cursor::operator++() -> Cursor &
{
    row_num_++;
    if (row_num_ >= table_->num_of_rows())
    {
        table_end_ = true;
    }
    return *this;
}
auto Cursor::operator++(int) -> Cursor { return ++(*this); }

auto Cursor::table() const -> Table * { return table_; }
auto Cursor::row_num() const -> int32_t { return row_num_; }
bool Cursor::table_end() const { return table_end_; }

#pragma endregion

#pragma region // Database Implementations

Database::Database() : table_(nullptr), dbname_()
{
}
void Database::dbopen(const char *filename)
{
    is_open_ = true;
    auto file_descriptor = // TODO:
        open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    auto file_length = lseek(file_descriptor, 0, SEEK_END);
    auto num_of_pages = file_length / database::PAGE_SIZE;
    auto pager = new Pager(file_descriptor, file_length, num_of_pages);
    auto num_of_rows = pager->file_length() / database::ROW_SIZE;
    table_ = new Table(pager, num_of_rows);
    dbname_ = filename;
}
void Database::dbclose() const
{
    auto pager = table_->pager();
    auto num_of_full_pages = table_->num_of_rows() / database::ROWS_PER_PAGE;
    for (auto i = 0; i < num_of_full_pages; i++)
    {
        if (pager->pages(i) == nullptr)
        {
            continue;
        }
        pager->flush(i, database::PAGE_SIZE);
        free(pager->pages(i));
        pager->nullptrify(i);
    }
    auto num_of_additional_rows =
        table_->num_of_rows() % database::ROWS_PER_PAGE;
    if (num_of_additional_rows > 0)
    {
        auto page_num = num_of_full_pages;
        if (pager->pages(page_num) != nullptr)
        {
            pager->flush(page_num, num_of_additional_rows * database::ROW_SIZE);
            free(pager->pages(page_num));
            pager->nullptrify(page_num);
        }
    }
    auto res = close(pager->file_descriptor());
    assert(res != -1);
    delete pager;
    delete table_;
    // TODO: 需要注释.
}

auto Database::table() const -> Table * { return table_; }
auto Database::dbname() const -> string { return dbname_; }
bool Database::is_open() const { return is_open_; }

#pragma endregion

Database db;

#endif // SIMPLEDB_CODE_DATABASE_HPP_
