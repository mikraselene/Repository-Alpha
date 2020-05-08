#include "../inc/input.h"
Input::Input(string in)
{
    input = in;
}
int Input::InputInt()
{
    CheckInput();
    int ans = int(GetAnswer());
    return ans;
}
double Input::InputReal()
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
double Input::InputRealWithCalc()
{
    double ans = Calc(input);
    if (ans >= 0)
    {
        return ans;
    }
    else
    {
        throw negative_number;
    }
}

void Input::CheckInput()
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
        throw illegal_number;
    }
    if (isNegative)
    {
        throw negative_number;
    }
}
double Input::GetAnswer()
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
double Input::Calc(string in)
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
                throw illegal_operation;
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
            throw illegal_number;
        }
    }

    double rawans = 0;
    int p = 0;
    for (int i = in.size() - 1; i >= 0; i--)
    {
        rawans += (in[i] - '0') * pow(10, p);
        p++;
    }

    double ans = rawans / pow(10, decim);
    return ans;
}