//OK
#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <cmath>

#include "date.h"
#include "text.h"

/*---------------------------------------------------------------------------
类名: In

描述:
    自定义输入类, 实现对输入数据的合法性检验. 
---------------------------------------------------------------------------*/
class In
{
public:
    friend std::istream &operator>>(std::istream &, In &);
    operator int();
    operator double();
    operator Date() const;
    operator std::string() const;

private:
    void CheckInput();
    double GetAnswer() const;
    int ToInt(const std::string &) const;
    std::string input;
};

class CalcIn
{
public:
    friend std::istream &operator>>(std::istream &, CalcIn &);
    operator double() const;

private:
    double Calc(std::string) const;
    std::string input;
};

#endif
