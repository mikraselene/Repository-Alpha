#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
int a, b;
int n;
int score = 0;
string answer;
string voc_a[10] = {"单主", "单属", "单与", "单宾", "单夺", "复主", "复属", "复与", "复宾", "复夺"};
string voc_b[6] = {"阳此", "阴此", "中此", "阳彼", "阴彼", "中彼"};
string key[10][6] = {{"hic", "haec", "hoc", "ille", "illa", "illud"},
                     {"huius", "huius", "huius", "illi-us", "illi-us", "illi-us"},
                     {"huic", "huic", "huic", "illi-", "illi-", "illi-"},
                     {"hunc", "hanc", "hoc", "illum", "illam", "illud"},
                     {"ho-c", "ha-c", "ho-c", "illo-", "illa-", "illo-"},
                     {"hi-", "hae", "haec", "illi-", "illae", "illa"},
                     {"ho-rum", "ha-rum", "ho-rum", "illo-rum", "illa-rum", "illo-rum"},
                     {"hi-s", "hi-s", "hi-s", "illi-s", "illi-s", "illi-s"},
                     {"ho-s", "ha-s", "haec", "illo-s", "illa-s", "illas"},
                     {"hi-s", "hi-s", "hi-s", "illi-s", "illi-s", "illi-s"}};
void exercises(int n)
{
    for (int i = 1; i <= n; i++)
    {
        srand(time(0));
        a = rand() % 10;
        b = rand() % 6;
        cout << i << ".\n";
        cout << voc_a[a] << voc_b[b] << ":  ";
        cin >> answer;
        if (answer == key[a][b])
        {
            cout << "ACCEPTED" << endl;
            score++;
        }
        else
        {
            cout << "WRONG ANSWER  答案: " << key[a][b] << endl;
        }
    }
}
void result(int score, int n, int t)
{
    cout << "------------------------------------------------------------\n";
    cout << "正确题数      " << score << " / " << n << endl;
    cout << "你的得分      " << 100 * score / n << " 分" << endl;
    cout << "共用时间      " << t / 60 << " 分 " << t % 60 << " 秒" << endl;
}
int main()
{
    cout << "请输入题目数量，n = ";
    cin >> n;
    int begin = time(0);
    exercises(n);
    int end = time(0);
    int t = end - begin;
    result(score, n, t);
}
