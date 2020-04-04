#include <iostream>
using namespace std;
class Integer
{
protected:
    int n;
};
class Vec : public Integer
{
public:
    Vec(int *t, int s)
    {
        n = s;
        v = new int[s];
        for (int i = 0; i < s; i++)
        {
            v[i] = t[i];
        }
    }
    Vec(int s)
    {
        n = s;
        v = new int[n];
    }
    friend Vec operator+(const Vec &A, const Vec &B)
    {
        int s = A.n;
        int T[s];
        for (int i = 0; i < s; i++)
        {
            T[i] = A.v[i] + B.v[i];
        }
        return Vec(T, s);
    }
    friend Vec operator-(const Vec &A, const Vec &B)
    {
        int s = A.n;
        int T[s];
        for (int i = 0; i < s; i++)
        {
            T[i] = A.v[i] - B.v[i];
        }
        return Vec(T, s);
    }
    friend int operator*(const Vec &A, const Vec &B)
    {
        int s = A.n;
        int result = 0;
        for (int i = 0; i < s; i++)
        {
            result += A.v[i] * B.v[i];
        }
        return result;
    }
    friend istream &operator>>(istream &input, Vec &A)
    {
        for (int i = 0; i < A.n; i++)
        {
            cin >> A.v[i];
        }
        return input;
    }
    friend ostream &operator<<(ostream &output, const Vec &A)
    {
        for (int i = 0; i < A.n - 1; i++)
        {
            cout << A.v[i] << " ";
        }
        cout << A.v[A.n - 1];
        return output;
    }

protected:
    int *v;
};

int main()
{
    char op = '+';
    int n = 0;
    while (cin >> op >> n)
    {
        Vec A(n);
        Vec B(n);
        cin >> A;
        cin >> B;
        if (op == '+')
        {
            cout << A + B << endl;
        }
        if (op == '-')
        {
            cout << A - B << endl;
        }
        if (op == '*')
        {
            cout << A * B << endl;
        }
    }
}