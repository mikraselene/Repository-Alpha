#include <iostream>
using namespace std;
int main()
{
    //理解作用域、引用和指针
    int i = 100, sum = 0;
    for (int i = 0; i != 10; ++i)
    {
        sum += i;
    }
    cout << i << " " << sum << endl;
    int ival = 114514;
    int &ref_val = ival;
    ival = 1919;
    cout << ref_val << endl;
    cout << "" << endl;
    int yjsp = 114514;
    int *homo = &yjsp;
    cout << "int yjsp = 114514;" << endl;
    cout << "int *homo = &yjsp;" << endl;
    cout << "therefore," << endl;
    cout << "yjsp = " << yjsp << endl;
    cout << "&yjsp = " << &yjsp << endl;
    cout << "homo = " << homo << endl;
    cout << "&homo = " << &homo << endl;
    cout << "*homo = " << *homo << endl;
    cout << "" << endl;
    *homo = 1919810;
    cout << "yjsp = " << yjsp << endl;
    cout << "&yjsp = " << &yjsp << endl;
    cout << "homo = " << homo << endl;
    cout << "&homo = " << &homo << endl;
    cout << "*homo = " << *homo << endl;
    cout << "" << endl;
    int *mur = &yjsp;
    int **kmr = &mur;
    cout << "yjsp = " << yjsp << endl;
    cout << "&yjsp = " << &yjsp << endl;
    cout << "mur = " << mur << endl;
    cout << "&mur = " << &mur << endl;
    cout << "*mur = " << *mur << endl;
    cout << "&*mur = " << &*mur << endl;
    cout << "*&mur = " << *&mur << endl;
    cout << "kmr = " << kmr << endl;
    cout << "*kmr = " << *kmr << endl;
    cout << "**kmr = " << **kmr << endl;
    cout << "&**kmr = " << &**kmr << endl;
    cout << "&*kmr = " << &*kmr << endl;
    cout << "*&*kmr = " << *&*kmr << endl;
    cout << "&kmr = " << &kmr << endl;
    cout << "*&kmr = " << *&kmr << endl;
    cout << "&*&kmr = " << &*&kmr << endl;
    cout << "**&kmr = " << **&kmr << endl;
    cout << "***&kmr = " << ***&kmr << endl;
}
