#include <string>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <cmath>
#define EXP_PTR_NUM 9 //运算符个数
#define EXP_FUN_NUM 9 //函数个数
#define EXP_DEBUG 1   //开启调试
#ifdef EXP_DEBUG
#include <iostream>
#endif

/* 单词符号类型 */
typedef enum
{
    TKT_NUMBER,   //数字
    TKT_OPERATOR, //运算符
    TKT_FUNCTION, //函数

    TKT_ENDSIGN, //结束符
    TKT_UNKNOW   //未知符号
} TokenType;

/* 表达式类 */
class Express
{
public:
    Express(const std::string &exp); //初始化表达式
    int getVal(double &res);         //求解值

private:
    std::string exp;   //表达式
    std::string token; //每次读取的单词
    TokenType tkType;  //读取的单词类型
    int pos, length;   //读取的位置和长度

    /* 静态数据 */
    static std::string ptrList[]; //支持的运算符
    static int ptrArgCnt[];       //运算符参数个数

    static std::string funList[];       //支持的函数列表
    static int funArgCnt[];             //运算符参数个数
    static int preceMap[][EXP_PTR_NUM]; //运算优先级表

    /* 调试输出 */
    void debug();

    /* 读取下一个单词 */
    void readToken();

    /* 比较两个运算符的优先 */
    int comaprePrece(const std::string &ptr1, const std::string &ptr2);

    /* 单步运算符计算 */
    double calculate(const std::string &ptr, double arg[]);

    /* 单步函数计算 */
    double callFun(const std::string &fun, double arg[]);

    /* 获取运算符序号 */
    int getPtrIndex(const std::string &ptr);

    /* 获取函数序号 */
    int getFunIndex(const std::string &fun);

    /* 从操作数栈获取n个参数 */
    bool getArg(std::stack<double> &opnd, double arg[], int n);
};

/* 初始化静态数据 */
std::string Express::ptrList[] = {"f(", ",", "+", "-", "*", "/", "(", ")", "#"};
int Express::ptrArgCnt[] = {0, 1, 2, 2, 2, 2, 0, 0, 0};

std::string Express::funList[] = {
    "sin(",
    "cos(",
    "tan(",
    "pow(",
    "pow2(",
    "pow3(",
    "max(",
    "min(",
    "sqrt(",
};
int Express::funArgCnt[] = {
    1,
    1,
    1,
    2,
    1,
    1,
    2,
    2,
    1,
};

int Express::preceMap[][EXP_PTR_NUM] = {
    //{f(, , +, -, *, /, (, ), #}
    {-1, -1, -1, -1, -1, -1, -1, 1, 1}, //f(
    {1, 1, 1, 1, 1, 1, 1, 1, 1},        //,
    {-1, 1, 1, 1, -1, -1, -1, 1, 1},    //+
    {-1, 1, 1, 1, -1, -1, -1, 1, 1},    //-
    {-1, 1, 1, 1, 1, 1, -1, 1, 1},      //*
    {-1, 1, 1, 1, 1, 1, -1, 1, 1},      ///
    {-1, 1, -1, -1, -1, -1, -1, 0, 1},  //(
    {1, 1, 1, 1, 1, 1, 1, 1, 1},        //)
    {-1, 1, -1, -1, -1, -1, -1, -1, 0}, //#
};

/******************************************************************************/

Express::Express(const std::string &exp)
{
    this->exp = exp + "#";
    this->token = "";
    this->pos = 0;
    this->length = 1 + exp.length();
    while (token != "#")
    {
        readToken();
        std::cout << token << " ";
    }
}

int Express::getPtrIndex(const std::string &ptr)
{
    for (int i = 0; i < EXP_PTR_NUM; ++i)
    {
        if (ptrList[i] == ptr)
        {
            return i;
        }
    }
    return -1;
}

int Express::getFunIndex(const std::string &fun)
{
    for (int i = 0; i < EXP_FUN_NUM; ++i)
    {
        if (funList[i] == fun)
        {
            return i;
        }
    }
    return -1;
}

int Express::comaprePrece(const std::string &ptr1, const std::string &ptr2)
{
    int m = getPtrIndex(ptr1), n = getPtrIndex(ptr2);
    if (m == -1)
    {
        m = 0;
    }
    if (n == -1)
    {
        n = 0;
    }
    return preceMap[m][n];
}

double Express::calculate(const std::string &ptr, double arg[])
{
    switch (getPtrIndex(ptr))
    {
    case 1:
        return arg[0];

    case 2:
        return arg[0] + arg[1];

    case 3:
        return arg[0] - arg[1];

    case 4:
        return arg[0] * arg[1];

    case 5:
        return arg[0] / arg[1];
    }
    return 0;
}

double Express::callFun(const std::string &fun, double arg[])
{
    switch (getFunIndex(fun))
    {
    case 0:
        return sin(arg[0]);

    case 1:
        return cos(arg[0]);

    case 2:
        return tan(arg[0]);

    case 3:
        return pow(arg[0], arg[1]);

    case 4:
        return arg[0] * arg[0];

    case 5:
        return arg[0] * arg[0] * arg[0];

    case 6:
        return arg[0] > arg[1] ? arg[0] : arg[1];

    case 7:
        return arg[0] < arg[1] ? arg[0] : arg[1];

    case 8:
        return sqrt(arg[0]);
    }
    return 0;
}

void Express::readToken()
{
    while (pos < length && exp[pos] == ' ')
    { //去掉前空格
        ++pos;
    }
    if (pos >= length)
    {
        tkType = TKT_ENDSIGN;
        return;
    }
    int pos_t = pos;
    char ch = exp[pos_t++];
    char ch_n = pos_t < length ? exp[pos_t] : 0;

    if (isdigit(ch) || (ch == '-' && isdigit(ch_n) && tkType != TKT_NUMBER))
    { //判断数字
        if (ch == '-')
        {
            ++pos_t;
        }
        while (pos_t < length && isdigit(ch = exp[pos_t]))
        {
            ++pos_t;
        }
        if (ch == '.')
        {
            ++pos_t;
            while (pos_t < length && isdigit(exp[pos_t]))
            {
                ++pos_t;
            }
        }
        tkType = TKT_NUMBER;
    }
    else if (-1 != getPtrIndex(std::string(1, ch)))
    { //判断运算符
        tkType = TKT_OPERATOR;
    }
    else if (isalpha(ch))
    { //判断函数
        while (pos_t < length && (isalnum(ch) || ch == '_'))
        {
            ch = exp[++pos_t];
        }
        if (ch == '(')
        {
            ++pos_t;
            if (-1 != getFunIndex(exp.substr(pos, pos_t - pos)))
            {
                tkType = TKT_FUNCTION;
            }
            else
            {
                tkType = TKT_UNKNOW;
            }
        }
        else
        {
            tkType = TKT_UNKNOW;
        }
    }
    else
    {
        tkType = TKT_UNKNOW;
    }
    token = exp.substr(pos, pos_t - pos);
    pos = pos_t;
}

bool Express::getArg(std::stack<double> &opnd, double arg[], int n)
{
    if (opnd.size() < n)
    {
        return false;
    }
    for (int i = n - 1; i >= 0; --i)
    {
        arg[i] = opnd.top();
        opnd.pop();
    }
    return true;
}

int Express::getVal(double &res)
{
    std::stack<std::string> optr; //算符栈
    std::stack<double> opnd;      //算数栈

    optr.push("#");
    pos = 0;
    readToken();

    while (tkType != TKT_ENDSIGN || !optr.empty())
    {
        /*#ifdef EXP_DEBUG
            std::cout << "TkT = " << tkType << ", ";
            std::cout << "Pos = " << pos << "/" << length << ", ";
            std::cout << "Token = '" << token << "'" << std::endl;
        #endif*/

        if (tkType == TKT_UNKNOW)
        {
            return -1; //未知符号
        }

        if (tkType == TKT_NUMBER)
        {
            opnd.push(atof(token.c_str()));
            readToken();
        }
        else
        {
            int comRes = comaprePrece(optr.top(), token);
            /*#ifdef EXP_DEBUG
                std::cout << "compare('" << optr.top() << "', '" << token << "') = " << comRes << std::endl;    
            #endif*/
            switch (comRes)
            {
            case -1:
                optr.push(token);
                readToken();
                break;

            case 1:
            {
                std::string ptr = optr.top();
                optr.pop();

                int idx = getPtrIndex(ptr), argCnt;
                double arg[10], res;
                if (-1 != idx)
                {
                    argCnt = ptrArgCnt[idx];
                    if (argCnt)
                    {
                        if (!getArg(opnd, arg, argCnt))
                        {
                            return -2; //表达式错误
                        }
                        res = calculate(ptr, arg);
                        opnd.push(res);
                    }
                }
                else
                {
                    idx = getFunIndex(ptr);
                    argCnt = funArgCnt[idx];
                    if (!getArg(opnd, arg, argCnt))
                    {
                        return -2; //表达式错误
                    }
                    res = callFun(ptr, arg);
                    opnd.push(res);
                    readToken();
                }
                break;
            }

            case 0:
                optr.pop();
                readToken();
                break;
            }
        }
    }
    res = opnd.top();
    return 0;
}
#include <cstdio>

using namespace std;

/* 输入一行字符串 */
string InputLine()
{
    string str;
    char ch;
    while ((ch = getchar()) != '\n')
    {
        str += ch;
    }
    return str;
}

int main()
{
    string input;
    while (cin >> input)
    {
        Express A(input);
    }
    /*
    string str; //sqrt(7.1 + 15/3)*max(5, min(2, 3)) - 1
    str = InputLine();
    while (str.length())
    {
        Express exp(str);
        double res;
       
        if (exp.getVal(res))
        {
            cout << "Express Error!" << endl;
        }
        else
        {
            cout << str << "=" << res << endl;
        }
        cout << endl;
        str = InputLine();
        
    }*/
    return 0;
}