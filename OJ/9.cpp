#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstdlib>
using namespace std;
typedef struct listnode //定义结构类型
{
    int data;
    struct listnode *pre;
    struct listnode *next;
} node, *list;

class figure
{
public:
    figure();
    ~figure();
    void creatlist();
    void reset();
    void insertf(int);
    void show();
    friend int listcompare(const figure &, const figure &);
    friend void sub(const figure &, const figure &, figure &);
    friend void add(const figure &, const figure &, figure &);
    friend void select(const figure &, const figure &, figure &, char);

private:
    list l;
    int len;
    char sym;
};
figure::figure() //创建初始链表,并初始化数据成员。
{
    sym = '+';
    len = 0;
    l = new node;
    if (l)
        l->pre = l->next = l;
    else
        exit(1);
}

figure::~figure() //析构函数，释放内存
{
    if (l) //防止对象被重复析构
    {
        reset();
        delete l;
        l = NULL;
    }
}
void figure::reset() //重置类的数据成员
{
    sym = '+';
    len = 0;
    list p = l->next, ptemp = NULL;
    while (p != l)
    {
        ptemp = p->next;
        delete p;
        p = ptemp;
    }
    l->pre = l->next = l;
}
void figure::creatlist() //接收数据利用尾插法建立链表
{
    list p = l, s;
    s = new node;
    while (cin >> s->data)
    {
        if (s->data < 0)
        {
            sym = '-';
            s->data *= -1;
        }
        s->next = l;
        s->pre = p;
        l->pre = s;
        p->next = s;
        p = s;
        len++;
        if (getchar() == '\n')
        {
            break;
        }
        s = new node;
    }
}
int listcompare(const figure &A, const figure &B) //比较两个数绝对值的大小
{
    int n1 = A.len, n2 = B.len;
    if (n1 > n2)
        return 1;
    else if (n1 < n2)
        return -1;
    else if (n1 == n2)
    {
        list a, b;
        a = A.l->next;
        b = B.l->next;
        while ((a->data == b->data) && (a != A.l) && (b != B.l))
        {
            a = a->next;
            b = b->next;
        }
        if (a->data > b->data)
            return 1; //a绝对值比b大,返回1
        else if (a->data < b->data)
            return -1; //a绝对值比b小，返回-1
        else
            return 0; //a和b的绝对值一样大，返回0
    }
    return 0;
}

void figure::insertf(int n) //在头节点后插入新节点
{
    len++;
    list q;
    q = new node;
    q->data = n;
    q->pre = l;
    q->next = l->next;
    l->next->pre = q;
    l->next = q;
}
void sub(const figure &a, const figure &b, figure &c) //实现减法运算，假定a的长度不小于b
{
    int bor = 0;
    list p, q;
    p = a.l->pre;
    q = b.l->pre;
    while (p != a.l && q != b.l)
    {
        int n = p->data - q->data - bor;
        if (n < 0)
        {
            n += 1000;
            bor = 1;
        }
        else
            bor = 0;
        c.insertf(n);
        p = p->pre;
        q = q->pre;
    }
    while (p != a.l)
    {
        int n = p->data - bor;
        if (n < 0)
        {
            n += 1000;
            bor = 1;
        }
        else
            bor = 0;
        c.insertf(n);
        p = p->pre;
    }
}

void add(const figure &a, const figure &b, figure &c) //实现加法运算
{
    int ext = 0;
    list p, q;
    p = a.l->pre;
    q = b.l->pre;
    while (p != a.l && q != b.l) //n1=n2,指长度
    {
        int n = p->data + q->data + ext;
        if (n >= 1000)
        {
            n -= 1000;
            ext = 1;
        }
        else
            ext = 0;
        c.insertf(n);
        p = p->pre;
        q = q->pre;
    }
    while (p != a.l) //n1>n2
    {
        int n = p->data + ext;
        if (n >= 1000)
        {
            n -= 1000;
            ext = 1;
        }
        else
            ext = 0;
        c.insertf(n);
        p = p->pre;
    }
    while (q != b.l) //n1<n2
    {
        int n = p->data + ext;
        if (n >= 1000)
        {
            n -= 1000;
            ext = 1;
        }
        else
            ext = 0;
        c.insertf(n);
        q = q->pre;
    }
}
void select(const figure &a, const figure &b, figure &c, char ope) //选择运算方法
{
    int num = listcompare(a, b);
    char sym1 = a.sym, sym2 = b.sym;
    if (ope == '+')
    {
        if (sym1 == '+' && sym2 == '+')
        {
            c.sym = '+'; //a+b
            add(a, b, c);
        }
        else if (sym1 == '+' && sym2 == '-')
        {
            if (num == 1) //a>b a-b
            {
                c.sym = '+';
                sub(a, b, c);
            }
            else if (num == -1) //a<b -(b-a)
            {
                c.sym = '-';
                sub(b, a, c);
            }
            else
                sub(a, b, c);
        }
        else if (sym1 == '-' && sym2 == '+')
        {
            if (num == 1) //a>b -(a-b)
            {
                c.sym = '-';
                sub(a, b, c);
            }
            else if (num == -1) //a<b b-a
            {
                c.sym = '+';
                sub(b, a, c);
            }
            else
                sub(a, b, c);
        }
        else if (sym1 == '-' && sym2 == '-') //-(a+b)
        {
            c.sym = '-';
            add(a, b, c);
        }
    }
    else if (ope == '-')
    {
        if (sym1 == '+' && sym2 == '+')
        {
            if (num == 1) //a>b a-b
            {
                c.sym = '+';
                sub(a, b, c);
            }
            else if (num == -1) //a<b -(b-a)
            {
                c.sym = '-';
                sub(b, a, c);
            }
            else
                sub(a, b, c);
        }
        else if (sym1 == '+' && sym2 == '-')
        {
            c.sym = '+'; //a+b
            add(a, b, c);
        }
        else if (sym1 == '-' && sym2 == '+')
        {
            c.sym = '-'; //-(a+b)
            add(a, b, c);
        }
        else if (sym1 == '-' && sym2 == '-')
        {
            if (num == 1) //a>b -(a-b)
            {
                c.sym = '-';
                sub(a, b, c);
            }
            else if (num == -1) //a<b b-a
            {
                c.sym = '+';
                sub(b, a, c);
            }
            else
                sub(a, b, c);
        }
    }
}
void figure::show()
{
    if (NULL == l)
        return;
    list p = l->next;
    while (p->data == 0 && p->next != l) //结果中遇到数据为0的结点跳过，直到数据不为0的结点
    {
        p = p->next;
    }
    if (p->data == 0 && p->next == l) //链表中全部结点为0
    {
        cout << "0";
        return;
    }
    if (sym == '-')
        cout << "-";
    cout << p->data;
    p = p->next;
    while (p != l)
    {
        cout << "," << setfill('0') << setw(3) << p->data;
        p = p->next;
    }
    cout << endl;
}
int main()
{
    int n;
    cin >> n;
    figure A, B, C;
    char op;
    while (n--)
    {
        cin >> op;
        A.creatlist();
        B.creatlist();
        select(A, B, C, op);
        C.show();
        A.reset();
        B.reset();
        C.reset();
    }
    return 0;
}