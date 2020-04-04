#include <iostream>
using namespace std;
class RMB
{
public:
    RMB(double r = 0)
    {
        if (r < 0)
        {
            mark = 0, r = -r;
        }
        else
        {
            mark = 1;
        }
        int n = int((r + 0.005) * 100);
        yuan = n / 100;
        jiao = (n % 100) / 10;
        fen = n % 10;
    }
    operator double()
    {
        if (mark)
        {
            return (yuan * 1.0 + jiao * 0.1 + fen * 0.01);
        }
        else
        {
            return -(yuan * 1.0 + jiao * 0.1 + fen * 0.01);
        }
    }
    RMB(const RMB &A)
    {
        yuan = A.yuan;
        jiao = A.jiao;
        fen = A.fen;
    }
    friend istream &operator>>(istream &input, RMB &A)
    {
        input >> A.yuan >> A.jiao >> A.fen;
        return input;
    }
    friend ostream &operator<<(ostream &output, const RMB &a)
    {
        if (!a.mark)
        {
            output << '-';
        }
        output << (int)abs(a.yuan) << "Y";
        output << (int)abs(a.jiao) << "J";
        output << (int)abs(a.fen) << "F" << endl;
        return output;
    }
    double number()
    {
        double t = 1.0;
        if (!mark)
        {
            t = -1.0;
        }
        return t * (yuan * 1.0 + jiao * 0.1 + fen * 0.01);
    }

private:
    int yuan;
    int jiao;
    int fen;
    bool mark;
};

int main()
{
    RMB a, b;
    double c;
    while (cin >> a)
    {
        cin >> b;
        cin >> c;
        cout << "a = " << a << "b = " << b << "c = " << RMB(c);
        cout << "a + c = " << RMB(a + c);
        cout << "a - b = " << RMB(a - b);
        cout << "b * 2 = " << RMB(b * 2);
        cout << "a * 0.5 = " << RMB(a * 0.5);
    }
}
