#include <vector>
#include <string>
#include <iostream>

using namespace std;

class BaseC
{
public:
    BaseC(string str1 = "BaseC")
    {
        str = str1;
    }
    virtual void show()
    {
        cout << str << endl;
    }

private:
    string str;
};

class SubC1 : public BaseC
{
public:
    SubC1(string str1 = "SubC1") : BaseC("BaseC_SubC1")
    {
        str = str1;
    }
    void show()
    {
        cout << str << endl;
    }

private:
    string str;
};

class SubC2 : public BaseC
{
public:
    SubC2(string str1 = "SubC2") : BaseC("BaseC_SubC2")
    {
        str = str1;
    }
    void show()
    {
        cout << str << endl;
    }

private:
    string str;
};

int main()
{
    vector<BaseC *> VecB(3);

    VecB[0] = new BaseC("vectorB");
    VecB[0]->show();
    VecB[1] = new SubC1();
    VecB[1]->show();
    VecB[2] = new SubC2();
    VecB[2]->show();
    VecB[2]->BaseC::show();

    return 0;
}