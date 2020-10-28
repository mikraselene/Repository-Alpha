#include <cstring>
#include <iostream>
using namespace std;

class Student
{
public:
    bool operator>(const Student &A) const
    {
        return sum > A.sum;
    }
    friend istream &operator>>(istream &input, Student &stu)
    {
        cin >> stu.id >> stu.name >> stu.gender;
        cin >> stu.English >> stu.Chinese >> stu.Maths;
        stu.sum = stu.English + stu.Chinese + stu.Maths;
        return input;
    }
    friend ostream &operator<<(ostream &output, const Student &stu)
    {
        cout << stu.id << "\t" << stu.name << "\t" << stu.gender << "\t";
        cout << stu.English << "\t" << stu.Chinese << "\t" << stu.Maths << "\t";
        cout << stu.sum << endl;
        return output;
    }

private:
    int id;
    string name;
    char gender;
    int English;
    int Chinese;
    int Maths;
    int sum;
};
void SelectSort(Student *st, int n)
{
    int i, j, t;
    Student temp;
    for (i = 0; i < n - 1; i++)
    {
        t = i;
        for (j = i + 1; j < n; j++)
        {
            if (st[j] > st[t])
            {
                t = j;
            }
        }
        if (t != i)
        {
            temp = st[i];
            st[i] = st[t];
            st[t] = temp;
        }
    }
    return;
}
int main()
{
    Student stu[5];
    int i;
    for (i = 0; i < 5; i++)
    {
        cin >> stu[i];
    }
    SelectSort(stu, 5);
    for (i = 0; i < 5; i++)
    {
        cout << stu[i] << endl;
    }
    return 0;
}
