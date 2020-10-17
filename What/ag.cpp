#include <iostream>

#define PROPERTY(type, name)      \
public:                           \
    void Set##name(const type &n) \
    {                             \
        name = n;                 \
    }                             \
    type Get##name()              \
    {                             \
        return name;              \
    }                             \
                                  \
private:                          \
    type name;

class Test
{
    PROPERTY(std::string, name);
    PROPERTY(int, value);
};

int main()
{
    Test A;
    A.Setname("hello");
    A.Setvalue(20);
    std::cout << A.Getname();
}