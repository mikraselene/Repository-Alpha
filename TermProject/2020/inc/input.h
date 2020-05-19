#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <cmath>

#include "date.h"
#include "text.h"

using std::string;

class NumberIn
{
public:
    NumberIn(string);
    int ToInt();
    double ToReal();

private:
    void CheckInput();
    double GetAnswer();

    string m_input;
};

class NumWithCalcIn
{
public:
    NumWithCalcIn(string);
    double ToRealWithCalc();

private:
    double Calc(string);

    string m_input;
};

class DateIn
{
public:
    DateIn(string);
    Date ToDate();

private:
    int ToInt(string);

    string m_input;
};

class StringIn
{
public:
    StringIn(string);
    string ToString();

private:
    string m_input;
};

#endif
