#include <iostream>
using namespace std;
class Book
{
public:
    int number;
    Book(string name, int p, int n)
    {
        bookname = name;
        price = p;
        number = n;
    }
    void Borrow()
    {
        number--;
    }
    void Restore()
    {
        number++;
    }
    void Display()
    {
        printf("%s\n", bookname.c_str());
        printf("%d\n%d\n", price, number);
    }

private:
    string bookname;
    int price;
};
int main()
{
    string name;
    int p;
    int n;
    while (cin >> name >> p >> n)
    {
        Book b(name, p, n);
        if (p < 50)
        {
            b.Borrow();
        }
        else
        {
            b.Restore();
        }
        b.Display();
    }
}