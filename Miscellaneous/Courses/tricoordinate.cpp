#include <iostream>
using namespace std;

class Tricoordinate
{
public:
    Tricoordinate(int mx = 0, int my = 0, int mz = 0)
    {
        x = mx;
        y = my;
        z = mz;
    }
    Tricoordinate operator+(Tricoordinate t)
    {
        Tricoordinate temp;
        temp.x = x + t.x;
        temp.y = y + t.y;
        temp.z = z + t.z;
        return temp;
    }
    Tricoordinate &operator++()
    {
        x++;
        y++;
        z++;
        return *this;
    }
    Tricoordinate &operator=(Tricoordinate t)
    {
        x = t.x;
        y = t.y;
        z = t.z;
        return *this;
    }
    void Show()
    {
        printf("(%d, %d, %d)\n", x, y, z);
    }
    void Assign(int mx, int my, int mz)
    {
        x = mx;
        y = my;
        z = mz;
    }

private:
    int x;
    int y;
    int z;
};

int main()
{
    Tricoordinate a(11, 45, 14);
    Tricoordinate b;
    Tricoordinate c;
    a.Show();
    b.Show();
    c.Show();
    for (int i = 0; i < 5; i++)
    {
        ++b;
    }
    b.Show();
    c.Assign(19, 19, 810);
    c = a + b + c;
    c.Show();
    c = b = a;
    c.Show();
}