#include <iostream>
using namespace std;
class Teachers
{
public:
    void Print()
    {
        cout << name << endl;
        int salary = fixedSalary + hourlyWage * classHour;
        cout << salary << endl;
    }

protected:
    int fixedSalary;
    int hourlyWage;
    int classHour;
    string name;
};
class Professor : public Teachers
{
public:
    Professor(int h, string n)
    {
        fixedSalary = 5000;
        hourlyWage = 50;
        classHour = h;
        name = n;
    }
};
class AssociateProfessor : public Teachers
{
public:
    AssociateProfessor(int h, string n)
    {
        fixedSalary = 3000;
        hourlyWage = 30;
        classHour = h;
        name = n;
    }
};
class Lecturer : public Teachers
{
public:
    Lecturer(int h, string n)
    {
        fixedSalary = 2000;
        hourlyWage = 20;
        classHour = h;
        name = n;
    }
};
int main()
{
    int flag = 0;
    string name;
    int h = 0;
    while (cin >> flag >> name >> h)
    {
        if (flag == 0)
        {
            Professor A(h, name);
            A.Print();
        }
        else if (flag == 1)
        {
            AssociateProfessor A(h, name);
            A.Print();
        }
        else if (flag == 2)
        {
            Lecturer A(h, name);
            A.Print();
        }
    }
}