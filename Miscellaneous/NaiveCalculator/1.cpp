#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

class Calculator
{
    stack<char> op;
    stack<double> val;
    enum
    {
        IN = 0,
        OUT = 1,
    };
    string opSet = "+-*/().";
    string input;
    double answer;

public:
    Calculator(string input)
    {
        this->input = input;
        DeleteSpace();
        IN2RPN();
        Calculate();
        cout << answer << endl;
    }

    double GetAnswer()
    {
        return answer;
    }

private:
    bool IsOperator(char op)
    {
        for (auto i : opSet)
        {
            if (op == i)
            {
                return 1;
            }
        }
        return 0;
    }

    int Priority(char op)
    {
        for (int i = 0; i < opSet.size(); i++)
        {
            if (op == opSet[i])
            {
                return i;
            }
        }
        return -1;
    }

    void DeleteSpace()
    {
        string result = "";
        for (auto i : input)
        {
            if (isdigit(i) || IsOperator(i))
            {
                result += i;
            }
            else if (i != ' ')
            {
                cerr << "err" << endl;
            }
        }
        input = result;
    }

    void IN2RPN()
    {
        int num = 0;
        int state = OUT;
        string result = "";
        input = input + '=';
        for (auto i : input)
        {
            if (isdigit(i))
            {
                num *= 10;
                num += i - '0';
                state = IN;
            }
            else
            {
                if (state == IN)
                {
                    result += to_string(num) + ' ';
                    num = 0;
                }
                if (i == '=')
                {
                    break;
                }
                else if (i == '(')
                {
                    op.push(i);
                }
                else if (i == ')')
                {
                    while (!op.empty() && op.top() != '(')
                    {
                        result += op.top();
                        result += ' ';
                        op.pop();
                    }
                    op.pop();
                }
                else
                {
                    while (1)
                    {
                        if (op.empty() || op.top() == '(')
                            op.push(i);
                        else if (Priority(i) > Priority(op.top()))
                            op.push(i);
                        else
                        {
                            result += op.top();
                            result += ' ';
                            op.pop();
                            continue;
                        }
                        break;
                    }
                }
                state = OUT;
            }
        }
        while (!op.empty())
        {
            result += op.top();
            result += ' ';
            op.pop();
        }
        input = result;
    }

    double ToReal(int a, int b)
    {
        return a + b * pow(10, -int(log10(b)) - 1);
    }

    void Calculate()
    {
        int num = 0;
        int state = OUT;
        for (auto i : input)
        {
            if (isdigit(i))
            {
                num *= 10;
                num += i - '0';
                state = IN;
            }
            else
            {
                if (state == IN)
                {
                    val.push(num);
                    num = 0;
                }
                double x, y;
                if (i != ' ')
                {
                    x = val.top();
                    val.pop();
                    y = val.top();
                    val.pop();
                    switch (i)
                    {
                    case '+':
                        val.push(y + x);
                        break;
                    case '-':
                        val.push(y - x);
                        break;
                    case '*':
                        val.push(y * x);
                        break;
                    case '/':
                        val.push(y / x);
                        break;
                    case '.':
                        val.push(y + x * pow(10, -int(log10(x)) - 1));
                    }
                }
                state = OUT;
            }
        }
        answer = val.top();
    }
};

int main()
{
    string s;
    while (cin >> s)
    {
        Calculator A(s);
    }
}
