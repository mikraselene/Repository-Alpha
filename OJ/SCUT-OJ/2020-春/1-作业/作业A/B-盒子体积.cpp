#include <iostream>
using namespace std;
class Box
{
public:
    Box()
    {
        length = 1;
        width = 1;
        height = 1;
    }
    void SetBox(int l, int w, int h)
    {
        length = l;
        width = w;
        height = h;
    }
    int Volume()
    {
        return length * width * height;
    }

private:
    int length;
    int width;
    int height;
};
int main()
{
    Box a;
    int l;
    int w;
    int h;
    while (cin >> l >> w >> h)
    {
        a.SetBox(l, w, h);
        cout << a.Volume() << endl;
    }
}