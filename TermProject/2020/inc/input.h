#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <cmath>

#include "date.h"
#include "text.h"

class NumberIn
{
public:
    NumberIn(std::string);
    int ToInt();
    double ToReal();

private:
    void CheckInput();
    double GetAnswer();
    std::string in;
};

class NumWithCalcIn
{
public:
    NumWithCalcIn(std::string);
    double ToRealWithCalc();

private:
    double Calc(std::string);
    std::string in;
};

class DateIn
{
public:
    DateIn(std::string);
    Date ToDate();

private:
    void CheckInput();
    int ToInt(std::string);
    std::string in;
    int year;
    int month;
    int day;
};

class StringIn
{
public:
    StringIn(std::string);
    std::string ToString();

private:
    std::string input;
};

#endif
