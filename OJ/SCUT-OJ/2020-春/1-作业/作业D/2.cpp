#include <iostream>
#include <algorithm>
using namespace std;
class Teachers
{
public:
    void Print()
    {
        cout << name << endl;
        cout << salary << endl;
    }
    int salary;

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
        salary = fixedSalary + hourlyWage * classHour;
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
        salary = fixedSalary + hourlyWage * classHour;
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
        salary = fixedSalary + hourlyWage * classHour;
    }
};
Teachers *t[1000];
bool cmp(Teachers *A, Teachers *B)
{
    return A->salary > B->salary;
}
int main()
{
    int flag = 0;
    string name;
    int h = 0;
    int i = 0;
    while (cin >> flag && flag != -1)
    {
        cin >> name >> h;
        if (flag == 0)
        {
            t[i++] = new Professor(h, name);
        }
        else if (flag == 1)
        {
            t[i++] = new AssociateProfessor(h, name);
        }
        else if (flag == 2)
        {
            t[i++] = new Lecturer(h, name);
        }
    }
    for (int j = 0; j < i; j++)
    {
        t[j]->Print();
    }
    sort(t, t + i, cmp);
    printf("%d\n%d\n", t[0]->salary, t[i - 1]->salary);
}