#ifndef SIMPLEDB_UTIL_HPP_
#define SIMPLEDB_UTIL_HPP_

#include <fmt/core.h>
#include <exception>
#include <iostream>
#include <ctime>
#include <string>
#include <array>

template <class T>
class Property
{
public:
    Property() {}
    explicit Property(const T &f) { val = f; }
    virtual ~Property() {}

    virtual auto operator=(const T &f) -> T & { return val = f; }
    virtual auto operator()() const -> const T & { return val; }
    virtual auto itself() -> T & { return val; }

protected:
    T val;
};

template <class T, int S>
class ArrayProperty
{
public:
    ArrayProperty() {}
    explicit ArrayProperty(const T &f) { val.fill(f); }
    explicit ArrayProperty(const std::array<T, S> &f) { val = f; }
    virtual ~ArrayProperty() {}

    virtual auto operator[](int i) -> T & { return val[i]; }
    virtual auto operator()() const -> const std::array<T, S> & { return val; }
    virtual auto itself() -> std::array<T, S> & { return val; }
    virtual void set(int i, const T &f) { val[i] = f; }

protected:
    std::array<T, S> val;
};

void print_msg()
{
    fmt::print("tssndb version 1.2.0\n");
    fmt::print("i.e. too simple sometimes naive database\n");
}
void print_prompt()
{
    fmt::print("MDB >>> ");
}
void print_prompt2()
{
    fmt::print("    ? > ");
}

struct invalid_arguments_num : public std::exception
{
    invalid_arguments_num(int exp, int got) : expected_num(exp), got_num(got) {}
    const char *what() const throw() { return "Invalid arguments num: "; }
    int expected_num;
    int got_num;
};
struct file_not_exist : public std::exception
{
    explicit file_not_exist(std::string file_name) : file_name(file_name) {}
    const char *what() const throw() { return "Database not exist."; }
    std::string file_name;
};
struct file_opening_error : public std::exception
{
    explicit file_opening_error(std::string file_name) : file_name(file_name) {}
    const char *what() const throw() { return "File opening error: "; }
    std::string file_name;
};
struct database_not_open : public std::exception
{
    const char *what() const throw() { return "No opening database."; }
};

class Clock
{
public:
    // Fiat iustitia, et pereat mundus.
    // —Ferdinand I, Holy Roman Emperor
    void verify()
    {
        state = State::TOCKED;
        start = clock();
        end = clock();
    }
    void tick()
    {
        assert(state == State::TOCKED);
        state = State::TICKED;
        start = clock();
    }
    void tock()
    {
        assert(state == State::TICKED);
        state = State::TOCKED;
        end = clock();
    }
    auto time_cost() -> double_t
    {
        assert(state == State::TOCKED);
        return double_t((end - start) * 1000 / CLOCKS_PER_SEC);
    }
    void print_time_cost() { printf("(%lf ms)", time_cost()); }

private:
    enum class State
    {
        INIT,
        TICKED,
        TOCKED,
    } state = State::TOCKED;
    clock_t start = clock();
    clock_t end = clock();
} clk;

#endif // SIMPLEDB_UTIL_HPP_
