#include <iostream>
using namespace std;

class OperatorTest
{
public:
    OperatorTest()
    {
        value = 0;
    }
    friend OperatorTest operator++(OperatorTest &a)
    {
        a.value++;
        return a;
    }
    friend OperatorTest operator++(OperatorTest &a, int)
    {
        OperatorTest temp(a);
        a.value++;
        return temp;
    }
    friend OperatorTest operator--(OperatorTest &a)
    {
        a.value--;
        return a;
    }
    friend OperatorTest operator--(OperatorTest &a, int)
    {
        OperatorTest temp(a);
        a.value--;
        return temp;
    }
    void Print()
    {
        printf("%d", value);
    }

private:
    int value;
};
int main()
{
    OperatorTest a;
    a.Print();
    a++;
    a.Print();
    ++a;
    a.Print();
}