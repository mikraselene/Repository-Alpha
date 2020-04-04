#include <iostream>
#include <cstring>
using namespace std;

class OperatorTest
{
public:
    OperatorTest(const char *pN)
    {
        printf("Constructing %s\n", pN);
        size = strlen(pN);
        pName = new char[size + 1];
        if (pName != 0)
        {
            strcpy(pName, pN);
        }
    }
    OperatorTest(const OperatorTest &obj)
    {
        printf("Copying %s\n", obj.pName);
        size = obj.size;
        pName = new char[size + 1];
        if (pName != 0)
        {
            strcpy(pName, obj.pName);
        }
    }
    OperatorTest &operator=(OperatorTest obj)
    {
        delete[] pName;
        size = obj.size;
        pName = new char[size + 1];
        if (pName != 0)
        {
            strcpy(pName, obj.pName);
        }
        return *this;
    }
    ~OperatorTest()
    {
        printf("Destructing %s\n", pName);
        pName[0] = '0';
        delete[] pName;
        pName = NULL;
        size = 0;
    }

protected:
    char *pName;
    int size;
};

int main()
{
    OperatorTest obj1("Hello");
    OperatorTest obj2 = obj1;
    OperatorTest obj3("Nemo");
    obj3 = obj2 = obj1;
}