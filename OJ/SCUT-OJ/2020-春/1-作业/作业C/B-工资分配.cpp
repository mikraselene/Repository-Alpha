#include <iostream>
using namespace std;
class Employee
{
public:
    Employee(string n = "Nemo")
    {
        name = n;
    }

protected:
    string name;
};
class Salesman : public Employee
{
public:
    Salesman(double s)
    {
        sales = s;
    }
    double Pay()
    {
        return sales / 200;
    }
    void Print()
    {
        printf("%.2lf\n", Pay());
    }

private:
    double sales;
};
class Salesmanager : public Employee
{
public:
    Salesmanager(double s)
    {
        sales = s;
    }

    void Print()
    {
        printf("%.2lf\n", 8000 + sales / 200);
    }

private:
    double sales;
};
int main()
{
    string name = "Nemo";
    bool isSalesmanager = 0;
    double sales = 0;
    while (cin >> name >> isSalesmanager >> sales)
    {
        if (isSalesmanager)
        {
            Salesmanager A(sales);
            A.Print();
        }
        else
        {
            Salesman B(sales);
            B.Print();
        }
    }
}