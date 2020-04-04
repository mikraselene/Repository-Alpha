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
int main()
{
    node *head = NULL;
    create(head);
    node *i;
    i = head;
    while (i)
    {
        cout << i->data << " ";
        i = i->next;
    }
}
