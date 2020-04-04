#include <iostream>
using namespace std;
int total = 0;
int cnt = 0;
class Student
{
public:
    Student()
    {
        score = 0;
    }
    Student(int s)
    {
        score = s;
    }

private:
    int score;
};
int main()
{
    int s;
    while (cin >> s && s != -1)
    {
        Student a(s);
        total += s;
        cnt++;
    }
    printf("%d\n%.1f\n", total, total * 1.0 / cnt);
}