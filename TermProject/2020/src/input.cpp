#include "../inc/input.h"

istream &operator>>(istream &in, In &A)
{
    getline(cin, A.m_input);
    return in;
}

/*---------------------------------------------------------------------------
FUNCTION: ToReal()

PURPOSE:
    To determine whether the return value of Calc() is negative or not.
    If the return value of Calc() is negative, throw ERR_NEGATIVE_NUMBER.

CALLS:
    Calc()

RETURN VALUE:
    The positive equivalent real value of the string.
---------------------------------------------------------------------------*/

In::operator int()
{
    CheckInput();
    int ans = int(GetAnswer());
    return ans;
}
In::operator double()
{
    int decim = 0;
    if (m_input.find('.') != m_input.npos)
    {
        decim = m_input.size() - m_input.find('.') - 1;
        m_input.erase(m_input.find('.'), 1);
    }
    CheckInput();
    double ans = GetAnswer() / pow(10, decim);
    return ans;
}
In::operator Date()
{
    auto first = m_input.find(" ");
    auto second = m_input.find_last_of(" ");
    auto third = m_input.size();
    if (m_input == "")
    {
        Date today;
        return today;
    }
    if (first == m_input.npos || second == m_input.npos || first == second)
    {
        throw ERR_ILLEGAL_DATE;
    }

    string yearstr = m_input.substr(0, first);
    string monthstr = m_input.substr(first + 1, second - first - 1);
    string daystr = m_input.substr(second + 1, third - second - 1);

    int year = ToInt(yearstr);
    int month = ToInt(monthstr);
    int day = ToInt(daystr);

    Year Y(year);
    Month M(month);
    Day D(day);
    Date date(Y, M, D);

    if (date.IsLegal() == 0)
    {
        throw ERR_ILLEGAL_DATE;
    }

    return date;
}
In::operator string()
{
    return m_input;
}

/*---------------------------------------------------------------------------
FUNCTION: CheckInput()

PURPOSE:
    Receive a string member and check whether it is legal or not.
    If it is not a number, throw ERR_ILLEGAL_NUMBER;
    If it is a negative number, throw ERR_NEGATIVE_NUMBER.
---------------------------------------------------------------------------*/
void In::CheckInput()
{
    bool isNegative = 0;
    if (m_input[0] == '+' || m_input[0] == '-')
    {
        isNegative = (m_input[0] == '-');
        m_input.erase(0, 1);
    }
    bool isIllegal = 0;
    for (int i = 0; i < m_input.size(); i++)
    {
        if (isdigit(m_input[i]) == 0)
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

/*---------------------------------------------------------------------------
FUNCTION: GetAnswer()

PURPOSE:
    Receive a number-legal string member and give it's number-equivalent value.

RETURN VALUE:
    The number-equivalent value of a number-legal string.
---------------------------------------------------------------------------*/
double In::GetAnswer()
{
    double rawans = 0;
    int p = 0;
    for (int i = m_input.size() - 1; i >= 0; i--)
    {
        rawans += (m_input[i] - '0') * pow(10, p);
        p++;
    }
    return rawans;
}

istream &operator>>(istream &in, CalcIn &A)
{
    getline(cin, A.m_input);
    return in;
}

CalcIn::operator double()
{
    double ans = Calc(m_input);
    if (ans >= 0)
    {
        return ans;
    }
    else
    {
        throw ERR_NEGATIVE_NUMBER;
    }
}

/*---------------------------------------------------------------------------
FUNCTION: Calc()

PURPOSE:
    Receive a string member and check whether it is legal or not.
    If it is legal, return the value of the equivalent real number.
    The string could contain space and the operator +, -, *, /.
    For example, the input string is "1 + 2/4", the function returns 1.5.

RETURN VALUE:
    The equivalent real value of the string.
---------------------------------------------------------------------------*/
double CalcIn::Calc(string input)
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
            string a = input.substr(0, input.find_last_of(op[i]));
            string b = input.substr(input.find_last_of(op[i]) + 1, input.size());
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
    if (input.find('.') != input.npos)
    {
        decim = input.size() - input.find('.') - 1;
        input.erase(input.find('.'), 1);
    }

    for (int i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i]) == 0)
        {
            throw ERR_ILLEGAL_NUMBER;
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

int In::ToInt(string input)
{
    for (int i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i]) == 0)
        {
            throw ERR_ILLEGAL_NUMBER;
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

// Previous
#if 0
/*---------------------------------------------------------------------------
FUNCTION: ToReal()

PURPOSE:
    To determine whether the return value of Calc() is negative or not.
    If the return value of Calc() is negative, throw ERR_NEGATIVE_NUMBER.

CALLS:
    Calc()

RETURN VALUE:
    The positive equivalent real value of the string.
---------------------------------------------------------------------------*/
double CalcIn::ToReal()
{
    double ans = Calc(m_input);
    if (ans >= 0)
    {
        return ans;
    }
    else
    {
        throw ERR_NEGATIVE_NUMBER;
    }
}

/*---------------------------------------------------------------------------
FUNCTION: ToInt()

PURPOSE:
    Receive a string member and check whether it is legal or not.
    If it is legal, return the value of the equivalent integer.

CALLS:
    CheckInput()
    GetAnswer()

RETURN VALUE:
    The equivalent int value of the string.
---------------------------------------------------------------------------*/
int In::ToInt()
{
    CheckInput();
    int ans = int(GetAnswer());
    return ans;
}

/*---------------------------------------------------------------------------
FUNCTION: ToReal()

PURPOSE:
    Receive a string member and check whether it is legal or not.
    If it is legal, return the value of the equivalent real number.

CALLS:
    CheckInput()
    GetAnswer()

RETURN VALUE:
    The equivalent real value of the string.
---------------------------------------------------------------------------*/
double In::ToReal()
{
    int decim = 0;
    if (m_input.find('.') != m_input.npos)
    {
        decim = m_input.size() - m_input.find('.') - 1;
        m_input.erase(m_input.find('.'), 1);
    }
    CheckInput();
    double ans = GetAnswer() / pow(10, decim);
    return ans;
}

/*---------------------------------------------------------------------------
FUNCTION: ToDate()

PURPOSE:
    Receive a string member and check whether it is legal or not.
    If it is legal, return the equivalent date.

CALLS:
    ToInt()
    IsLegal()

RETURN VALUE:
    The equivalent date of the string.
---------------------------------------------------------------------------*/
Date In::ToDate()
{
    auto first = m_input.find(" ");
    auto second = m_input.find_last_of(" ");
    auto third = m_input.size();
    if (m_input == "")
    {
        Date today;
        return today;
    }
    if (first == m_input.npos || second == m_input.npos || first == second)
    {
        throw ERR_ILLEGAL_DATE;
    }

    string yearstr = m_input.substr(0, first);
    string monthstr = m_input.substr(first + 1, second - first - 1);
    string daystr = m_input.substr(second + 1, third - second - 1);

    int year = ToInt(yearstr);
    int month = ToInt(monthstr);
    int day = ToInt(daystr);

    Year Y(year);
    Month M(month);
    Day D(day);
    Date date(Y, M, D);

    if (date.IsLegal() == 0)
    {
        throw ERR_ILLEGAL_DATE;
    }

    return date;
}

#endif