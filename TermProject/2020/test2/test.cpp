#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class LeastSquare
{
    double k, b;
    vector<double> x;
    vector<double> y;

public:
    LeastSquare(vector<double> y)
    {
        this->y = y;
        x.resize(y.size());
        for (int i = 0; i < y.size(); i++)
        {
            x[i] = i;
        }
        k = 0;
        b = 0;
    }
    void Fitting()
    {
        double Sx = 0;
        double Sx2 = 0;
        double Sy = 0;
        double Sxy = 0;
        double n = x.size();
        /*
        Sx = Σ(0, n)x[i]
        Sx2 = Σ(0, n)x^2[i]
        Sy = Σ(0, n)y[i]
        Sxy = Σ(0, n)x[i]y[i]

             nΣx[i]y[i] - Σx[i] * Σy[i]
        k = ----------------------------
                nΣx[i]^2 - (Σx[i])^2
        
             Σx[i]^2 * Σy[i] - Σx[i] * Σx[i]y[i]
        b = -------------------------------------
                    nΣ(x[i]^2 - (Σx[i])^2
        */
        for (int i = 0; i < n; i++)
        {
            Sx += x[i];
            Sx2 += x[i] * x[i];
            Sy += y[i];
            Sxy += x[i] * y[i];
        }
        k = (n * Sxy - Sx * Sy) / (n * Sx2 - Sx * Sx);
        b = (Sx2 * Sy - Sx * Sxy) / (n * Sx2 - Sx * Sx);
    }

    double Y(const double x) const
    {
        return k * x + b;
    }
};

int main()
{

    vector<double> y = {114, 514, 1919, 810};

    LeastSquare ls(y);
    ls.Fitting();
    cout << "X\t";
    for (int i = 0; i <= y.size(); i++)
    {
        cout << i << "\t";
    }
    cout << endl;
    cout << "Y\t";
    for (int i = 0; i < y.size(); i++)
    {
        cout << y[i] << "\t";
    }
    cout << ls.Y(y.size()) << endl;
}