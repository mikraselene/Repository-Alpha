#include <iostream>
using namespace std;
class Complex
{
public:
    Complex(double r = 0, double i = 0)
    {
        real = r;
        imaginary = i;
    }
    Complex(int r)
    {
        real = r;
        imaginary = 0;
    }
    void Print()
    {
        printf("c = %g + %gi\n", real, imaginary);
    }
    friend Complex operator+(const Complex &c1, const Complex &c2)
    {
        double r = c1.real + c2.real;
        double i = c1.imaginary + c2.imaginary;
        return Complex(r, i);
    }
    friend Complex operator-(const Complex &c1, const Complex &c2)
    {
        double r = c1.real - c2.real;
        double i = c1.imaginary - c2.imaginary;
        return Complex(r, i);
    }
    friend Complex operator-(const Complex &c)
    {
        return Complex(-c.real, -c.imaginary);
    }

private:
    double real;
    double imaginary;
};

int main()
{
    Complex c1(11.4, 51.4);
    Complex c2(19.19, 8.10);
    Complex c;
    c = c1 - c2;
    c.Print();
    c = 25 + c2;
    c.Print();
    c = c2 + 25;
    c.Print();
    c = -c1;
    c.Print();
}