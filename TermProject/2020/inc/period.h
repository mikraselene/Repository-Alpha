#ifndef PERIOD_H
#define PERIOD_H

#include <iostream>
#include <vector>

#include "date.h"
#include "text.h"

using std::cout;
using std::endl;
using std::string;

class Period
{
public:
    friend std::ostream &operator<<(std::ostream &, Period);
    Period();
    Period(int);
    int CalculateWeekly();
    int CalculateDaily();
    int CalculateMonthly();

private:
    enum
    {
        monthly = 1,
        weekly = 2,
        daily = 3,
    };
    int code;
    string period;
    int day;
    int amount;
    Date start;
};

#endif
