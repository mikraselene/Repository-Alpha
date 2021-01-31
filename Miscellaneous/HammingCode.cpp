#include <iostream>
#include <functional>
#include <algorithm>
#include <complex>
#include <ctime>

auto main() -> int
{
    std::string str;
    std::cin >> str;
    auto cp = 0, ans = 0;
    auto size = [str]() -> int {
        auto len = 0;
        while (str.size() > (1 << len) - len)
            len++;
        return len;
    }() + str.size();
    bool code[size], flag = false;
    for (auto i = 0; i < size; i++)
        if ((code[i] = (i + 1 & i ? str[cp++] - '0' : false)))
            flag ? ans = ans ^ i + 1 : ans = i + 1, flag = true;
    for (auto mask = 1; mask < size; mask <<= 1)
        code[mask - 1] = mask & ans;
    std::for_each(code, code + size, [](auto i) { std::cout << i; });
}
