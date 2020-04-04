#include <iostream>
using namespace std;
class NauticalMile
{
public:
    NauticalMile(double km, double m)
    {
        kilometer = km;
        meter = m;
    }
    void Print()
    {
        printf("%.4lf\n", double(*this));
    }
    operator double()
    {
        return (kilometer + meter / 1000.0) / 1.852;
    }

private:
    double kilometer;
    double meter;
};

int main()
{
    double km = 0;
    double m = 0;
    while (cin >> km >> m)
    {
        NauticalMile A(km, m);
        A.Print();
    }
}