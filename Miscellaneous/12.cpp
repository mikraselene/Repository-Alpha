
#include <iostream>
using namespace std;

class A
{
public:
    virtual void fun()
    {
    }

protected:
    int s;
};
class B : public A
{
private:
    void fun()
    {
        s = 0;
        printf("b%d\n", s);
    }
};
class C : public A
{
public:
    void fun()
    {
        printf("c\n");
    }
};
int main(void)
{
    B b;
    C c;
    A *p = &b;
    A *q = &c;
    p->fun();
    q->fun();
    return 0;
}
