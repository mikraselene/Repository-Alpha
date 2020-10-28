#include <iostream>
using namespace std;
struct node
{
    int data;
    node *next;
};
void create(node *&head)
{
    node *s, *p;
    s = new node;
    cin >> s->data;
    while (s->data != 0)
    {
        if (head == NULL)
            head = s;
        else
            p->next = s;
        p = s;
        s = new node;
        cin >> s->data;
    }
    p->next = NULL;
    delete s;
}
void del(node *&head)
{
    node *i, *p;
    i = head;
    while (i->next != NULL)
    {
        p = i;
        if (i->next->data == 9)
        {
            p = i->next;
            i->next = p->next;
        }
        i = i->next;
    }
}
int main()
{
    node *head = NULL;
    create(head);
    del(head);
    node *i;
    i = head;
    while (i)
    {
        cout << i->data << " ";
        i = i->next;
    }
}
