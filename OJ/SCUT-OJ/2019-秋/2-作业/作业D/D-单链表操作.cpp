#include <iostream>
using namespace std;
struct node
{
    int id;
    int age;
    char sex;
    node *next;
};
node *head = NULL;
void display(node *head)
{
    node *i;
    i = head;
    while (i)
    {
        cout << i->id << " " << i->age << " " << i->sex << endl;
        i = i->next;
    }
}
node *create(int n)
{
    node *s, *p;
    s = new node;
    cin >> s->id >> s->age >> s->sex;
    head = s;
    while (n--)
    {
        p = s;
        s = new node;
        if (n)
            cin >> s->id >> s->age >> s->sex;
        p->next = s;
    }
    node *r = p;
    p->next = NULL;
    return r;
}
void insert(node *h, int m)
{
    node *s, *p;
    s = new node;
    cin >> s->id >> s->age >> s->sex;
    h->next = s;
    while (m--)
    {
        p = s;
        s = new node;
        if (m)
            cin >> s->id >> s->age >> s->sex;
        p->next = s;
    }
    p->next = NULL;
}
void count(node *head)
{
    node *i;
    i = head;
    int m = 0;
    int f = 0;
    while (i)
    {
        if (i->sex == 'm')
            m++;
        if (i->sex == 'f')
            f++;
        i = i->next;
    }
    cout << "Number of male employees:" << m << endl;
    cout << "Number of female employees:" << f << endl;
}
void del(node *&head)
{
    node *i, *p;
    i = head;
    int cnt = 1;
    while (i)
    {
        if (cnt == 1)
        {
            p = i;
        }
        if (cnt == 2)
        {
            p->next = i->next;
        }
        i = i->next;
        cnt++;
    }
}
int main()
{
    int n;
    while (cin >> n)
    {
        node *p = create(n);
        display(head);
        int m;
        cin >> m;
        insert(p, m);
        display(head);
        count(head);
        del(head);
        display(head);
    }
}
