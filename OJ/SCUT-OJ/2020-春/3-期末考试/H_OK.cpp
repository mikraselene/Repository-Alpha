#include <iostream>
#include <cmath>

using namespace std;

class Time
{
public:
    Time(int hour, int minute, int second)
    {
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    }
    Time(int time)
    {
        second = time % 60;
        time -= second;
        minute = (time / 60) % 60;
        time /= 60;
        time -= minute;
        hour = (time / 60) % 60;
    }
    operator int()
    {
        int time = hour * 60 * 60 + minute * 60 + second;
        return time;
    }

    friend Time operator+(Time A, Time B)
    {
        Time S = int(A) + int(B);
        return S;
    }
    friend Time operator-(Time A, Time B)
    {
        Time S = abs(int(A) - int(B));
        return S;
    }
    int GetHour()
    {
        return hour;
    }
    int GetMinute()
    {
        return minute;
    }
    int GetSecond()
    {
        return second;
    }
    void Print()
    {
        cout << hour << ":" << minute << ":" << second;
    }

private:
    int hour;
    int minute;
    int second;
};
int main()
{
    int n = 0;
    cin >> n;
    while (n--)
    {
        int h1 = 0;
        int m1 = 0;
        int s1 = 0;
        int h2 = 0;
        int m2 = 0;
        int s2 = 0;
        cin >> h1 >> m1 >> s1 >> h2 >> m2 >> s2;
        Time A(h1, m1, s1);
        Time B(h2, m2, s2);
        Time S = A + B;
        Time P = A - B;
        S.Print();
        cout << " ";
        P.Print();
        cout << endl;
    }
}