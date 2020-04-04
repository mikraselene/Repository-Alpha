// 利用sizeof求解数据类型所要求的字节数
#include <iostream>
using namespace std;
int main()
{
    cout << "char:" << sizeof(char) << endl;
    cout << "short int:" << sizeof(short int) << endl;
    cout << "int:" << sizeof(int) << endl;
    cout << "long int:" << sizeof(long int) << endl;
    cout << "double:" << sizeof(double) << endl;
    cout << "long double:" << sizeof(long double) << endl;
}
