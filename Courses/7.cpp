#include <iostream>
using namespace std;
class Calculator
{
public:
    Calculator()
    {
        value = 0;
    }
    void operator++();
    void operator--();
    unsigned int operator()();

private:
    unsigned int value;
};
void Calculator::operator++()
{
    if (value < 65535)
    {
        ++value;
    }
    else
    {
        printf("Data Overflow.\n");
        abort();
    }
}
void Calculator::operator--()
{
    if (value > 0)
    {
        --value;
    }
    else
    {
        printf("Data Overflow.\n");
        abort();
    }
}
unsigned int Calculator::operator()()
{
    return value;
}
int main()
{
    Calculator counter;
    int i;
    for (i = 0; i <= 5; i++)
    {
        ++counter;
        printf("counter = %d\n", counter());
    }
    for (i = 0; i <= 10; i++)
    {
        --counter;
        printf("counter = %d\n", counter());
    }
}