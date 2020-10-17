#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
class Complex
{
public:
    Complex(double real, double imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }
    Complex(double real)
    {
        this->real = real;
        this->imaginary = 0;
    }

    Complex operator++()
    {
        real = real + 1;
        imaginary = imaginary + 1;
        return *this;
    }
    Complex operator++(int)
    {
        real = real + 1;
        imaginary = imaginary + 1;
        return *this;
    }
    Complex operator--()
    {
        real = real - 1;
        imaginary = imaginary - 1;
        return *this;
    }
    Complex operator--(int)
    {
        real = real - 1;
        imaginary = imaginary - 1;
        return *this;
    }

    Complex operator=(Complex c)
    {
        *this = c;
        return *this;
    }

    friend Complex operator+(Complex a, Complex b)
    {
        double real = a.real + b.real;
        double imaginary = a.imaginary + b.imaginary;
        return Complex(real, imaginary);
    }
    friend Complex operator-(Complex a, Complex b)
    {

        double real = a.real - b.real;
        double imaginary = a.imaginary - b.imaginary;
        return Complex(real, imaginary);
    }
    friend Complex operator*(Complex a, Complex b)
    {
        double real = a.real * b.real - a.imaginary * b.imaginary;
        double imaginary = a.real * b.imaginary + a.imaginary * b.real;
        return Complex(real, imaginary);
    }
    friend Complex operator/(Complex a, Complex b)
    {
        double r = b.real * b.real + b.imaginary * b.imaginary;
        double real = (a.real * b.real + a.imaginary * b.imaginary) / r;
        double imaginary = (-a.real * b.imaginary + a.imaginary * b.real) / r;
        return Complex(real, imaginary);
    }

    Complex operator+=(Complex c)
    {
        this->real = this->real + c.real;
        this->imaginary = this->imaginary + c.imaginary;
        return *this;
    }
    Complex operator-=(Complex c)
    {

        this->real = this->real - c.real;
        this->imaginary = this->imaginary - c.imaginary;
        return *this;
    }
    Complex operator*=(Complex c)
    {
        this->real = this->real * c.real - this->imaginary * c.imaginary;
        this->imaginary = this->real * c.imaginary + this->imaginary * c.real;
        return *this;
    }
    Complex operator/=(Complex c)
    {
        double r = c.real * c.real + c.imaginary * c.imaginary;
        this->real = (this->real * c.real + this->imaginary * c.imaginary) / r;
        this->imaginary = (-this->real * c.imaginary + this->imaginary * c.real) / r;
        return *this;
    }

    double operator[](int n)
    {
        return pow(pow(real, n) + pow(imaginary, n), 1.0 / n);
    }
    string operator()()
    {
        double r = real * real + imaginary * imaginary;
        double theta = atan(imaginary / real);
        string exp = to_string(r) + " * exp(i * " + to_string(theta / 3.1415926) + "π)";
        return exp;
    }
    operator double()
    {
        return (*this)[2];
    }
    operator string()
    {
        return (*this)();
    }

    friend bool operator==(Complex a, Complex b)
    {
        return a.real == b.real && a.imaginary == b.imaginary;
    }
    friend bool operator!=(Complex a, Complex b)
    {
        return a.real != b.real || a.imaginary != b.imaginary;
    }

    friend ostream &operator<<(ostream &out, Complex c)
    {
        double r = c.real;
        double i = c.imaginary;
        if (r == 0)
        {
            if (i == 0)
            {
                out << 0;
            }
            else
            {
                if (i < 0)
                {
                    out << "-";
                }
                if (abs(i) != 1)
                {
                    out << abs(i);
                }
                out << "i";
            }
        }
        else
        {
            out << r;
            if (i != 0)
            {
                i > 0 ? out << " + " : out << " - ";
                if (abs(i) != 1)
                {
                    out << abs(i);
                }
                out << "i";
            }
        }
        return out;
    }

private:
    double real;
    double imaginary;
};

class T
{
    friend void f(T &, int);
    int i;
};
void f(T &t, int k)
{
    k += t.i;
}
int main()
{
    double a, b;
    while (cin >> a >> b)
    {
        Complex c(a, b);
        //cout << sin(3);
        //cout << c << endl;
        char s[4] = "abd";
        cout << a;
    }
}