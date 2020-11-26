#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;
template <typename T>
class stack
{
    T p[40];
    int toop;

public:
    stack() { toop = -1; }
    void push(T t)
    {
        toop++;
        p[toop] = t;
    }
    T top() { return p[toop]; }
    bool empty()
    {
        if (toop == -1)
            return true;
        return false;
    }
    void pop() { toop--; }
};
class caculator
{
    string s; //原波兰式的容器
    stack<char> op;
    stack<float> num;
    stringstream ss; //用于转换的流
    stringstream sb; //插入逆波兰式的流
    string str;      //存放数字的容器，每次更新
    string strs;     //存放逆波兰式的容器
    float x, y;

public:
    caculator(char *p) { s = p; }
    float trans(const char *p);
    float antipoland();
    void show() { cout << strs; }
    void readnum();
    void caucEveTime();
    void shownum()
    {
        while (!num.empty())
        {
            cout << num.top() << endl;
            num.pop();
        }
    }
    void showop()
    {
        while (!op.empty())
        {
            cout << op.top() << endl;
            op.pop();
        }
    }
    bool checkpoint(const char *p);
};
bool caculator::checkpoint(const char *p)
{
    int i = strlen(p);
    while (i--)
    {
        if (*p == '.')
            return true;
        p++;
    }
    return false;
}
float caculator::trans(const char *p) //底层const,对象为常量
{
    float n = 0;
    float m = 0;
    int i = strlen(p);
    int j; //记录小数点后有几位
    if (checkpoint(p))
    {
        while (--i && (*p != '.'))
        {
            n = n * 10 + (*p - '\0' - 48);
            p++;
        }
        --i;
        p++; //跳过小数点
        j = i;
        m = *p - '\0' - 48; //确保转化成int后数值不变,*p指向第一位
        while (i--)
        {
            p++;
            m = m * 10 + (*p - '\0' - 48);
        }
        return n + m * pow(0.1, j + 1);
    }
    else
    {
        while (i--)
        {
            n = n * 10 + (*p - '\0' - 48);
            p++;
        }
        return n;
    }
}
void caculator::readnum()
{
    str = ss.str();
    if (!str.empty()) //str中存放数字串
    {
        ss.str(""); //清空流
        num.push(trans(str.c_str()));
    }
}
void caculator::caucEveTime() //由符号栈弹出符号决定调用
{
    y = num.top();
    num.pop();
    x = num.top();
    num.pop();
    switch (op.top())
    {
    case '+':
        num.push(x + y);
        break;
    case '-':
        num.push(x - y);
        break;
    case '*':
        num.push(x * y);
        break;
    case '/':
        num.push(x / y);
        break;
    default:
        break;
    }
}
float caculator::antipoland()
{
    for (int i = 0; i < s.size(); i++)
        switch (s[i])
        {
        case '(':
            op.push(s[i]);
            readnum();
            break;
        case '+':
        case '-':
            readnum();
            while (op.top() != '(' && !op.empty())
            {
                if (op.top() != '(' && op.top() != ')')
                {
                    sb << op.top();
                }
                op.pop();
            }
            op.push(s[i]);

            break;
        case ')':
            readnum();
            while (op.top() != '(')
            {
                sb << op.top();
                caucEveTime();
                op.pop();
            }
            op.pop();
            break;
        case '*':
        case '/':
            readnum();
            while (op.top() == '*' || op.top() == '/')
            {
                sb << op.top();
                caucEveTime();
                op.pop();
            }
            op.push(s[i]);
            break;
        default:
            sb << s[i];
            ss << s[i];
            break;
        }
    str = ss.str();
    if (!str.empty())
        num.push(trans(str.c_str()));

    while (!op.empty())
    {
        if (op.top() != '(' && op.top() != ')')
        {
            sb << op.top();
            caucEveTime();
        }
        op.pop();
    }

    strs = sb.str();
    return num.top();
}
int main()
{
    while (1)
    {
        char ch[40];
        char *p = ch;
        cin >> p;
        caculator a(p);
        //a.antipoland();//两次重复调用改变数字栈中的数字！
        //a.show();
        //cout << endl;
        cout << "=" << a.antipoland() << endl;
        // cout << endl;
        //a.shownum();
        //a.showop();}
    }
}