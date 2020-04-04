#include <iostream>
using namespace std;
class Rectangle
{
protected:
    int length;
    int width;
};
class Rectanglar : public Rectangle
{
public:
    friend istream &operator>>(istream &in, Rectanglar &A)
    {
        in >> A.length >> A.width >> A.height;
        return in;
    }
    int Volume()
    {
        int volume = length * width * height;
        return volume;
    }

private:
    int height;
};

int main()
{
    Rectanglar A;
    while (cin >> A)
    {
        cout << A.Volume() << endl;
    }
}