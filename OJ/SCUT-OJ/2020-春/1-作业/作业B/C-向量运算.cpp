#include <iostream>
using namespace std;
class Vec
{
public:
    Vec(int s = 1)
    {
        size = s;
        v = new int[size];
    }
    Vec(int *temp, int s)
    {
        size = s;
        v = new int[s];
        for (int i = 0; i < s; i++)
        {
            v[i] = temp[i];
        }
    }
    Vec &operator=(const Vec &A)
    {
        size = A.size;
        for (int i = 0; i < size; i++)
        {
            v[i] = A.v[i];
        }
        return *this;
    }
    friend Vec operator+(const Vec &A, const Vec &B)
    {
        int s = A.size;
        int T[s];
        for (int i = 0; i < s; i++)
        {
            T[i] = A.v[i] + B.v[i];
        }
        return Vec(T, s);
    }
    friend Vec operator-(const Vec &A, const Vec &B)
    {
        int s = A.size;
        int T[s];
        for (int i = 0; i < s; i++)
        {
            T[i] = A.v[i] - B.v[i];
        }
        return Vec(T, s);
    }
    friend int operator*(const Vec &A, const Vec &B)
    {
        int sum = 0;
        for (int i = 0; i < A.size; i++)
        {
            sum += A.v[i] * B.v[i];
        }
        return sum;
    }
    friend istream &operator>>(istream &input, Vec &A)
    {
        for (int i = 0; i < A.size; i++)
        {
            scanf("%d", &A.v[i]);
        }
        return input;
    }
    friend ostream &operator<<(ostream &output, const Vec &A)
    {
        int s = A.size;
        printf("(");
        for (int i = 0; i < s - 1; i++)
        {
            printf("%d,", A.v[i]);
        }
        printf("%d)", A.v[s - 1]);
        return output;
    }

private:
    int size;
    int *v;
};
int main()
{
    int sizeA = 0;
    int sizeB = 0;
    while (cin >> sizeA)
    {
        Vec A(sizeA);
        cin >> A;

        cin >> sizeB;
        Vec B(sizeB);
        cin >> B;
        if (sizeA == sizeB)
        {
            cout << "X=" << A << endl;
            cout << "Y=" << B << endl;
            cout << "X+Y=" << A + B << endl;
            cout << "X-Y=" << A - B << endl;
            cout << "X*Y=" << A * B << endl;
        }
        else
        {
            cout << "error" << endl;
        }
    }
}