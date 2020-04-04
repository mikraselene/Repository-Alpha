#include <algorithm>
#include <iostream>
using namespace std;
struct List
{
    int data;
    List *next;
};
void Count(List *&head)
{
    List *i;
    i = head;
    int cnt = 1;
    while (i)
    {
        if (i->next != NULL && i != head)
        {
            if (i->data == i->next->data)
            {
                cnt++;
            }
            else
            {
                if (cnt > 1)
                    cout << i->data << ":" << cnt << endl;
                cnt = 1;
            }
        }
        if (i->next == NULL)
        {
            if (cnt > 1)
                cout << i->data << ":" << cnt << endl;
        }
        i = i->next;
    }
}
int main()
{
    int n;
    int i;
    while (cin >> n)
    {
        int a[1000];
        for (i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        sort(a, a + n);
        List *head = new List();
        head->next = NULL;
        List *q = new List();
        q = head;
        for (i = 0; i < n; i++)
        {
            List *p = new List();
            p->data = a[i];
            p->next = NULL;
            q->next = p;
            q = q->next;
        }
        Count(head);
    }
}
