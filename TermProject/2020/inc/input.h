#include <iostream>
#include <cmath>
#include "date.h"

using namespace std;

class NumberIn
{
public:
    NumberIn(string);
    int ToInt();
    double ToReal();

private:
    void CheckInput();
    double GetAnswer();
    string in;
};

class NumWithCalcIn
{
public:
    NumWithCalcIn(string);
    double ToRealWithCalc();

private:
    double Calc(string);
    string in;
};

class DateIn
{
public:
    DateIn(string);
    Date ToDate();

private:
    void CheckInput();
    int ToInt(string);
    string in;
    int year;
    int month;
    int day;
};

class StringIn
{
public:
    StringIn(string);
    string ToString();

private:
    string input;
};