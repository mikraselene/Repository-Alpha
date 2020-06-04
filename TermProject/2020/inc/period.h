#ifndef PERIOD_H
#define PERIOD_H

#include <iostream>
#include <memory>
#include <vector>

#include "date.h"
#include "text.h"

/*---------------------------------------------------------------------------
类名: Period

描述:
    自定义 Period 数据类型, 实现对周期基本的计数, 输出等功能. 
---------------------------------------------------------------------------*/
class Period
{
public:
    friend std::ostream &operator<<(std::ostream &, const Period &);
    Period();
    Period(const int &);
    operator int();
    int Calculate(const Date &) const;

    enum
    {
        NO_PERIOD = 0,
        MONTHLY = 1,
        WEEKLY = 2,
        DAILY = 3,
    };

private:
    int code;
    std::string period;
};

#endif
