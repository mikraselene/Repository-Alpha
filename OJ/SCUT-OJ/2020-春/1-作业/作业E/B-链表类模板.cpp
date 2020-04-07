#include <iostream>
#include <stack>
using namespace std;

template <typename T>
class List
{
public:
    List(T x)
    {
        data = x;
    }
    void Add(List *node)
    {
        node->next = this;
        next = 0;
    }
    T GetData()
    {
        return data;
    }
    List *GetNext()
    {
        return next;
    }

private:
    T data;
    List *next;
};

int main()
{
    int n = 0;
    while (cin >> n)
    {
        int headData = 0;
        cin >> headData;
        List<int> head(headData);
        List<int> *p;
        List<int> *last;
        last = &head;
        for (int i = 1; i < n; i++)
        {
            int data = 0;
            cin >> data;
            p = new List<int>(data);
            p->Add(last);
            last = p;
        }
        int *reverse = new int[n];
        p = &head;
        int k = n - 1;
        while (p)
        {
            reverse[k--] = p->GetData();
            p = p->GetNext();
        }
        for (int i = 0; i < n - 1; i++)
        {
            cout << reverse[i] << " ";
        }
        cout << reverse[n - 1] << endl;
    }
}