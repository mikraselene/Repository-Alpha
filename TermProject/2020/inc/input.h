#include <iostream>
#include <cmath>
using namespace std;

const string illegal_operation = "不合法的运算";
const string illegal_number = "不合法的数字";
const string negative_number = "输入不能为负数";

class Input
{
public:
    Input(string);
    int InputInt();
    double InputReal();
    double InputRealWithCalc();

private:
    void CheckInput();
    double GetAnswer();
    double Calc(string);
    string input;
};