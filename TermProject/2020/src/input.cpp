#include "../inc/input.h"

using namespace std;

#pragma region "Input Pure Number"

NumberIn::NumberIn(string input)
{
    in = input;
}
int NumberIn::ToInt()
{
    CheckInput();
    int ans = int(GetAnswer());
    return ans;
}
double NumberIn::ToReal()
{
    int decim = 0;
    if (in.find('.') != in.npos)
    {
        decim = in.size() - in.find('.') - 1;
        in.erase(in.find('.'), 1);
    }
    CheckInput();
    double ans = GetAnswer() / pow(10, decim);
    return ans;
}
void NumberIn::CheckInput()
{
    bool isNegative = 0;
    if (in[0] == '+' || in[0] == '-')
    {
        isNegative = (in[0] == '-');
        in.erase(0, 1);
    }
    bool isIllegal = 0;
    for (int i = 0; i < in.size(); i++)
    {
        if (isdigit(in[i]) == 0)
        {
            isIllegal = 1;
        }
    }
    if (isIllegal)
    {
        throw ERR_ILLEGAL_NUMBER;
    }
    if (isNegative)
    {
        throw ERR_NEGATIVE_NUMBER;
    }
}
double NumberIn::GetAnswer()
{
    double rawans = 0;
    int p = 0;
    for (int i = in.size() - 1; i >= 0; i--)
    {
        rawans += (in[i] - '0') * pow(10, p);
        p++;
    }
    return rawans;
}

#pragma endregion

#pragma region "Input Number"

NumWithCalcIn::NumWithCalcIn(string input)
{
    in = input;
}
double NumWithCalcIn::ToRealWithCalc()
{
    double ans = Calc(in);
    if (ans >= 0)
    {
        return ans;
    }
    else
    {
        throw ERR_NEGATIVE_NUMBER;
    }
}
double NumWithCalcIn::Calc(string in)
{
    char op[5] = "+-*/";
    for (int i = 0; i < in.size(); i++)
    {
        if (in[i] == ' ')
        {
            in.erase(i, 1);
        }
    }
    if (in[0] == '+' || in[0] == '-')
    {
        in = "0" + in;
    }

    for (int i = 0; i < 5; i++)
    {
        if (in.find_last_of(op[i]) != in.npos)
        {
            string a = in.substr(0, in.find_last_of(op[i]));
            string b = in.substr(in.find_last_of(op[i]) + 1, in.size());
            if (a.size() == 0 || b.size() == 0)
            {
                throw ERR_ILLEGAL_OPERATION;
            }
            switch (op[i])
            {
            case '+':
                return Calc(a) + Calc(b);
            case '-':
                return Calc(a) - Calc(b);
            case '*':
                return Calc(a) * Calc(b);
            case '/':
                return Calc(a) / Calc(b);
            }
        }
    }

    int decim = 0;
    if (in.find('.') != in.npos)
    {
        decim = in.size() - in.find('.') - 1;
        in.erase(in.find('.'), 1);
    }

    for (int i = 0; i < in.size(); i++)
    {
        if (isdigit(in[i]) == 0)
        {
            throw ERR_ILLEGAL_NUMBER;
        }
    }
    double rawans = 0;
    int p = 0;
    for (int i = in.size() - 1; i >= 0; i--)
    {
        rawans += (in[i] - '0') * pow(10, p);
        p++;
    }
    return rawans;
    double ans = rawans / pow(10, decim);
    return ans;
}

#pragma endregion

#pragma region "Input Date"

DateIn::DateIn(string input)
{
    in = input;
}
Date DateIn::ToDate()
{
    auto first = in.find(" ");
    auto second = in.find_last_of(" ");
    auto third = in.size();
    if (in == "")
    {
        Date today;
        return today;
    }
    if (first == in.npos || second == in.npos || first == second)
    {
        throw ERR_ILLEGAL_DATE;
    }

    string yearstr = in.substr(0, first);
    string monthstr = in.substr(first + 1, second - first - 1);
    string daystr = in.substr(second + 1, third - second - 1);

    int year = ToInt(yearstr);
    int month = ToInt(monthstr);
    int day = ToInt(daystr);

    Year Y(year);
    Month M(month);
    Day D(day);
    date = Date(Y, M, D);

    CheckInput();

    return date;
}
void DateIn::CheckInput()
{
    if (date.isLegal() == 0)
    {
        throw ERR_ILLEGAL_DATE;
    }
}
int DateIn::ToInt(string in)
{
    for (int i = 0; i < in.size(); i++)
    {
        if (isdigit(in[i]) == 0)
        {
            throw ERR_ILLEGAL_NUMBER;
        }
    }
    int ans = 0;
    int p = 0;
    for (int i = in.size() - 1; i >= 0; i--)
    {
        ans += (in[i] - '0') * pow(10, p);
        p++;
    }
    return ans;
}

#pragma endregion

StringIn::StringIn(string in)
{
    input = in;
}
string StringIn::ToString()
{
    return input;
}
