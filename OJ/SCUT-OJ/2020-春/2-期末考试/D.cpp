// D

#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class Array
{
public:
    Array(int num)
    {
        this->num = num;
    }
    void set(T n, int i)
    {
        arr[i] = n;
    }
    T getMax()
    {
        sort(arr, arr + num);
        return arr[num - 1];
    }

private:
    T arr[114514];
    int num;
};

int main()
{
    int n;
    while (cin >> n)
    {
        Array<int> a_int(n);
        int number;
        for (int i = 0; i < n; i++)
        {
            cin >> number;
            a_int.set(number, i);
        }
        cout << a_int.getMax() << endl;

        Array<double> a_dou(n);
        double d;
        for (int i = 0; i < n; i++)
        {
            cin >> d;
            a_dou.set(d, i);
        }
        cout << a_dou.getMax() << endl;

        Array<char> a_char(n);
        char c;
        for (int i = 0; i < n; i++)
        {
            cin >> c;
            a_char.set(c, i);
        }
        cout << a_char.getMax() << endl;
    }
    return 0;
}