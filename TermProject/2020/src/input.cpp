//OK
#include "../inc/input.h"

#pragma region "Public"

std::istream &operator>>(std::istream &in, In &A)
{
    getline(std::cin, A.input);
    return in;
}

/*---------------------------------------------------------------------------
重载: operator int()

目的:
    接收 string 成员变量并检查其是否合法. 如果其是合法的, 返回其等效整形值 x. 

返回值:
    整数 x.
---------------------------------------------------------------------------*/
In::operator int()
{
    CheckInput();
    int ans = int(GetAnswer());
    return ans;
}

/*---------------------------------------------------------------------------
重载: operator double()

目的:
    接收 string 成员变量并检查其是否合法. 如果其是合法的, 返回其等效实数值 x. 

返回值:
    实数 x.
---------------------------------------------------------------------------*/
In::operator double()
{
    int decim = 0;
    if (input.find('.') != input.npos)
    {
        decim = input.size() - input.find('.') - 1;
        input.erase(input.find('.'), 1);
    }
    CheckInput();
    double ans = GetAnswer() / pow(10, decim);
    return ans;
}

/*---------------------------------------------------------------------------
重载: operator int()

目的:
    接收 string 成员变量并检查其是否合法. 如果其是合法的, 返回其等效日期 x. 

返回值:
    日期 x.
---------------------------------------------------------------------------*/
In::operator Date() const
{
    auto first = input.find(" ");
    auto second = input.find_last_of(" ");
    auto third = input.size();
    if (input == "")
    {
        Date today;
        return today;
    }
    if (first == input.npos || second == input.npos || first == second)
    {
        throw NError::ILLEGAL_DATE;
    }

    std::string yearstr = input.substr(0, first);
    std::string monthstr = input.substr(first + 1, second - first - 1);
    std::string daystr = input.substr(second + 1, third - second - 1);

    int year = ToInt(yearstr);
    int month = ToInt(monthstr);
    int day = ToInt(daystr);

    Year Y(year);
    Month M(month);
    Day D(day);
    Date date(Y, M, D);

    if (date.IsLegal() == 0)
    {
        throw NError::ILLEGAL_DATE;
    }

    return date;
}

In::operator std::string() const
{
    return input;
}

std::istream &operator>>(std::istream &in, CalcIn &A)
{
    getline(std::cin, A.input);
    return in;
}

/*---------------------------------------------------------------------------
重载: operator double()

目的:
    检查 Calc() 的返回值 x 是否是正数, 如果是则返回 x 本身, 否则抛出负数异常.

返回值:
    实数 x.
---------------------------------------------------------------------------*/
CalcIn::operator double() const
{
    double ans = Calc(input);
    if (ans >= 0)
    {
        return ans;
    }
    else
    {
        throw NError::NEGATIVE_NUMBER;
    }
}

#pragma endregion

#pragma region "Private"

/*---------------------------------------------------------------------------
函数: void CheckInput()

目的:
    接收接收 string 成员变量并检查其是否合法:
    如果其不是一个数字, 则抛出不合法数字异常;
    如果其是一个负数, 则抛出负数异常.
---------------------------------------------------------------------------*/
void In::CheckInput()
{
    bool isNegative = 0;
    if (input[0] == '+' || input[0] == '-')
    {
        isNegative = (input[0] == '-');
        input.erase(0, 1);
    }
    bool isIllegal = 0;
    for (int i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i]) == 0)
        {
            isIllegal = 1;
        }
    }
    if (isIllegal)
    {
        throw NError::ILLEGAL_NUMBER;
    }
    if (isNegative)
    {
        throw NError::NEGATIVE_NUMBER;
    }
}

/*---------------------------------------------------------------------------
函数: double GetAnswer()

目的:
    接收一个合法的 string 并返回其等效整形值 x.

返回值:
    整数 x.
---------------------------------------------------------------------------*/
double In::GetAnswer() const
{
    double rawans = 0;
    int p = 0;
    for (int i = input.size() - 1; i >= 0; i--)
    {
        rawans += (input[i] - '0') * pow(10, p);
        p++;
    }
    return rawans;
}

/*---------------------------------------------------------------------------
函数: double Calc()

目的:
    接收 string 成员变量并检查其是否合法. 如果其是合法的, 返回其等效实数值 x. 
    合法的 string 可以包括空格和四则运算符号, 例如接收 "1 + 2/4", 返回 1.5.

返回值:
    实数 x.
---------------------------------------------------------------------------*/
double CalcIn::Calc(std::string input) const
{
    char op[5] = "+-*/";
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == ' ')
        {
            input.erase(i, 1);
        }
    }
    if (input[0] == '+' || input[0] == '-')
    {
        input = "0" + input;
    }

    for (int i = 0; i < 5; i++)
    {
        if (input.find_last_of(op[i]) != input.npos)
        {
            std::string a = input.substr(0, input.find_last_of(op[i]));
            std::string b = input.substr(input.find_last_of(op[i]) + 1, input.size());
            if (a.size() == 0 || b.size() == 0)
            {
                throw NError::ILLEGAL_OPERATION;
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
    if (input.find('.') != input.npos)
    {
        decim = input.size() - input.find('.') - 1;
        input.erase(input.find('.'), 1);
    }

    for (int i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i]) == 0)
        {
            throw NError::ILLEGAL_NUMBER;
        }
    }
    double rawans = 0;
    int p = 0;
    for (int i = input.size() - 1; i >= 0; i--)
    {
        rawans += (input[i] - '0') * pow(10, p);
        p++;
    }
    return rawans;
    double ans = rawans / pow(10, decim);
    return ans;
}

/*---------------------------------------------------------------------------
函数: int ToInt()

目的:
    接收 string 成员变量并检查其是否整形合法. 如果其是合法的, 返回其等效整形值 x.

返回值:
    整数 x.
---------------------------------------------------------------------------*/
int In::ToInt(const std::string &input) const
{
    for (int i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i]) == 0)
        {
            throw NError::ILLEGAL_NUMBER;
        }
    }
    int ans = 0;
    int p = 0;
    for (int i = input.size() - 1; i >= 0; i--)
    {
        ans += (input[i] - '0') * pow(10, p);
        p++;
    }
    return ans;
}

#pragma endregion
