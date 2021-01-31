#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include <stack>
#include <map>
#include <exception>
#include <memory>

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::multimap;
using std::ostream_iterator;
using std::pair;
using std::stack;
using std::string;
using std::vector;

clock_t clock_start_ = clock();
clock_t clock_end_ = clock();
#define TICK clock_start_ = clock()
#define TOCK clock_end_ = clock()
#define TIME_COST (double)(clock_end_ - clock_start_) / CLOCKS_PER_SEC
#define PRINT_TIME_COST printf("%lf s\n", TIME_COST)

#define RESET "\e[0m"
#define BLACK "\e[90m"
#define RED "\e[91m"
#define GREEN "\e[92m"
#define YELLOW "\e[93m"
#define BLUE "\e[94m"
#define MAGENTA "\e[95m"
#define CYAN "\e[96m"
#define WHITE "\e[97m"

#define PRINT(xx) printf(xx RESET)

#endif