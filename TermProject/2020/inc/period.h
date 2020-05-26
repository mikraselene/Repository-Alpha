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
    int Calculate(Date);
    operator int();

    enum
    {
        NO_PERIOD = 0,
        MONTHLY = 1,
        WEEKLY = 2,
        DAILY = 3,
    };

private:
    int code;
    string period;
};

#endif
