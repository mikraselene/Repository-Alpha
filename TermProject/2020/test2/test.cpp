#include <iostream>
using namespace std;

class A
{
protected:
    int a;
};
class B : public A
{
public:
    friend istream &operator>>(istream &in, B &alpha)
    {
        cin >> alpha.a;
        return in;
    }
    void print()
    {
        cout << a;
    }
};
class C : public A
{
public:
    friend istream &operator>>(istream &in, C &alpha)
    {
        cin >> alpha.a;
        return in;
    }
    void print()
    {
        cout << a;
    }
};
int main()
{
    B b;
    cin >> b;
    b.print();
}