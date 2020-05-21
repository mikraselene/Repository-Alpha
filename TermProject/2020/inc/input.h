#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <cmath>

#include "date.h"
#include "text.h"

using std::istream;
using std::string;

class In
{
protected:
    string m_input;
};
class NumberIn : public In
{
public:
    friend istream &operator>>(istream &, NumberIn &);
    int ToInt();
    double ToReal();

private:
    void CheckInput();
    double GetAnswer();
};

class NumWithCalcIn : public In
{
public:
    friend istream &operator>>(istream &, NumWithCalcIn &);
    double ToReal();

private:
    double Calc(string);
};

class DateIn : public In
{
public:
    friend istream &operator>>(istream &, DateIn &);
    Date ToDate();

private:
    int ToInt(string);
};

class StringIn : public In
{
public:
    friend istream &operator>>(istream &, StringIn &);
    string ToString();
};

#endif
