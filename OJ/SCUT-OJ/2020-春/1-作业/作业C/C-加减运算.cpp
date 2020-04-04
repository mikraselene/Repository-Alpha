#include <iostream>
using namespace std;
class Integer
{
protected:
    int plus(int a, int b)
    {
        return a + b;
    }
    int minus(int a, int b)
    {
        return a - b;
    }
};
class Real
{
protected:
    double plus(double a, double b)
    {
        return a + b;
    }
    double minus(double a, double b)
    {
        return a - b;
    }
};
class IntReal : public Integer, public Real
{
public:
    IntReal()
    {
        op = '+';
        isReal = 0;
        x = 0;
        y = 0;
    }
    void Print()
    {
        if (isReal)
        {
            if (op == '+')
            {
                printf("%.2f\n", Real::plus(x, y));
            }
            else if (op == '-')
            {
                printf("%.2f\n", Real::minus(x, y));
            }
        }
        else
        {
            int tx = int(x);
            int ty = int(y);
            if (op == '+')
            {
                printf("%d\n", Integer::plus(x, y));
            }
            else if (op == '-')
            {
                printf("%d\n", Integer::minus(x, y));
            }
        }
    }
    friend istream &operator>>(istream &in, IntReal &A)
    {
        in >> A.op >> A.isReal >> A.x >> A.y;
        return in;
    }

private:
    char op;
    bool isReal;
    double x;
    double y;
};

int main()
{
    IntReal A;
    while (cin >> A)
    {
        A.Print();
    }
}