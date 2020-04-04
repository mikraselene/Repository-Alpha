#include <iostream>
using namespace std;
struct cplx
{
    double real;
    double img;
};
int main()
{
    char optr;
    cplx a, b, c;
    while (cin >> a.real >> a.img >> b.real >> b.img >> optr)
    {
        if (optr == '+')
        {
            c.real = a.real + b.real;
            c.img = a.img + b.img;
        }
        if (optr == '-')
        {
            c.real = a.real - b.real;
            c.img = a.img - b.img;
        }
        if (optr == '*')
        {
            c.real = a.real * b.real - a.img * b.img;
            c.img = a.real * b.img + a.img * b.real;
        }
        if (optr == '/')
        {
            c.real = a.real * b.real + a.img * b.img;
            c.img = -a.real * b.img + a.img * b.real;
            c.real /= (b.real * b.real + b.img * b.img);
            c.img /= (b.real * b.real + b.img * b.img);
        }
        if (c.real != 0)
        {
            cout << "c=" << c.real;
            if (c.img > 0)
                cout << "+" << c.img << "i" << endl;
            else if (c.img < 0)
                cout << c.img << "i" << endl;
        }
        else if (c.real == 0)
        {
            cout << "c=";
            if (c.img > 0)
                cout << "+" << c.img << "i" << endl;
            else if (c.img < 0)
                cout << c.img << "i" << endl;
            else
                cout << "0" << endl;
        }
    }
}
