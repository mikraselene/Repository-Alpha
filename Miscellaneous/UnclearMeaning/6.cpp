#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;
template <typename T>
class sci
{
    int xh;
    string n;
    char g;
    T en;
    T ch;
    T ma;
    T wu;
    T hua;
    T sh;
    T sum;

public:
    sci(int xh1 = 0, string n1 = " ", char g1 = ' ', T en1 = 0, T ch1 = 0, T ma1 = 0, T wu1 = 0, T hua1 = 0, T sh1 = 0, T sum1 = 0)
    {
        xh = xh1;
        n = n1;
        g = g1;
        en = en1;
        ch = ch1;
        ma = ma1;
        wu = wu1;
        hua = hua1;
        sh = sh1;
        sum = sum1;
    }
};
template <typename T>
class art
{
    int xh;
    string n;
    char g;
    T en;
    T ch;
    T ma;
    T di;
    T li;
    T zh;
    T sum;

public:
    art(int xh1 = 0, string n1 = " ", char g1 = ' ', T en1 = 0, T ch1 = 0, T ma1 = 0, T di1 = 0, T li1 = 0, T zh1 = 0, T sum1 = 0)
    {
        xh = xh1;
        n = n1;
        g = g1;
        en = en1;
        ch = ch1;
        ma = ma1;
        di = di1;
        li = li1;
        zh = zh1;
        sum = sum1;
    }
};
template <typename T>
class other
{
    int xh;
    string n;
    char g;
    T en;
    T ch;
    T ma;
    T sub1;
    T sub2;
    T sub3;
    T sum;

public:
    other(int xh1 = 0, string n1 = " ", char g1 = ' ', T en1 = 0, T ch1 = 0, T ma1 = 0, T sub11 = 0, T sub22 = 0, T sub33 = 0, T sum1 = 0)
    {
        xh = xh1;
        n = n1;
        g = g1;
        en = en1;
        ch = ch1;
        ma = ma1;
        sub1 = sub11;
        sub2 = sub22;
        sub3 = sub33;
        sum = sum1;
    }
};
int main()
{
    sci<double> sc[5];
    sci<double> *ss[5];
    art<double> ar[5];
    art<double> *aa[5];
    other<double> ot[5];
    other<double> *oo[5];
    fstream fin;
    int i = 0, j = 0, xue = 0;
    string s;
    char g;
    double n1, n2, n3, n4, n5, n6, total = 0;
    ifstream infile("SiceceStudent", ios::in);
    infile.seekg(0, ios::beg);
    cout << "\n理科生成绩单：\n"
         << setw(10) << "学号" << setw(20) << "姓名" << setw(3) << "性别" << setw(10) << "英语" << setw(10) << "语文"
         << setw(10) << "数学" << setw(10) << "物理" << setw(10) << "化学" << setw(10) << "生物" << setw(10) << "总分" << endl;
    while (infile >> xue >> s >> g >> n1 >> n2 >> n3 >> n4 >> n5 >> n6)
    {
        cout << setw(10) << xue << setw(20) << s << setw(3) << g << setw(10) << n1 << setw(10) << n2 << setw(10) << n3 << setw(10) << n4 << setw(10) << n5 << setw(10) << n6 << setw(10) << total << endl;
        total = n1 + n2 + n3 + n4 + n5 + n6;
        sc[i] = sci<double>(xue, s, g, n1, n2, n3, n4, n5, n6, total);
        ss[i] = &sc[i];
    }
    ifstream infile2("LiberalArtsStudent", ios::in);
    infile2.seekg(0, ios::beg);
    while (infile >> xue >> s >> g >> n1 >> n2 >> n3 >> n4 >> n5 >> n6)
    {
        cout << setw(10) << xue << setw(20) << s << setw(3) << g << setw(10) << n1 << setw(10) << n2 << setw(10) << n3 << setw(10) << n4 << setw(10) << n5 << setw(10) << n6 << setw(10) << total << endl;
        total = n1 + n2 + n3 + n4 + n5 + n6;
        ar[i] = (xue, s, g, n1, n2, n3, n4, n5, n6, total);
        aa[i] = &ar[i];
    }
}