#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <cmath>

#include "date.h"
#include "text.h"

using std::cin;
using std::istream;
using std::string;

class In
{
public:
    friend istream &operator>>(istream &, In &);
    operator int();
    operator double();
    operator Date();
    operator string();

private:
    void CheckInput();
    double GetAnswer();
    int ToInt(string);
    string input;
};

class CalcIn
{
public:
    friend istream &operator>>(istream &, CalcIn &);
    operator double();

private:
    double Calc(string);
    string input;
};

#endif
