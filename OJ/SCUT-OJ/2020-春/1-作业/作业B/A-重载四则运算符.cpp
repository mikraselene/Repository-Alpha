#include <iostream>
using namespace std;
class Integer
{
public:
    Integer(int n)
    {
        num = n;
    }
    friend Integer operator+(Integer &A, Integer &B)
    {
        int s = A.num + B.num;
        Integer T(s);
        return Integer(T);
    }
    friend Integer operator-(Integer &A, Integer &B)
    {
        int s = A.num - B.num;
        Integer T(s);
        return Integer(T);
    }
    friend Integer operator*(Integer &A, Integer &B)
    {
        int s = A.num * B.num;
        Integer T(s);
        return Integer(T);
    }
    friend Integer operator/(Integer &A, Integer &B)
    {
        int s = A.num / B.num;
        Integer T(s);
        return Integer(T);
    }
    friend void Print(Integer &A)
    {
        if (A.num > 32767 || A.num < -32768)
        {
            cout << "Data Overflow!" << endl;
        }
        else
        {
            cout << A.num << endl;
        }
    }

private:
    int num;
};

int main()
{
    int a = 0;
    int b = 0;
    char op = '+';
    while (cin >> a >> b >> op)
    {
        Integer A(a);
        Integer B(b);
        if (op == '+')
        {
            Integer T = A + B;
            Print(T);
        }
        if (op == '-')
        {
            Integer T = A - B;
            Print(T);
        }
        if (op == '*')
        {
            Integer T = A * B;
            Print(T);
        }
        if (op == '/')
        {
            Integer T = A / B;
            Print(T);
        }
    }
}