#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
using namespace std;

template <typename T>
class Science
{
public:
    Science()
    {
        id = 0;
        name = "Unknown";
        gender = 'U';
        english = 0;
        chinese = 0;
        maths = 0;
        physics = 0;
        chemistry = 0;
        biology = 0;
        sum = 0;
    }
    Science(int t, string n, char g, T *p, T s)
    {
        id = t;
        name = n;
        gender = g;
        english = p[0];
        chinese = p[1];
        maths = p[2];
        physics = p[3];
        chemistry = p[4];
        biology = p[5];
        sum = s;
    }

private:
    int id;
    string name;
    char gender;
    T english;
    T chinese;
    T maths;
    T physics;
    T chemistry;
    T biology;
    T sum;
};

template <typename T>
class Arts
{
public:
    Arts()
    {
        id = 0;
        name = "Unknown";
        gender = 'U';
        english = 0;
        chinese = 0;
        maths = 0;
        geography = 0;
        history = 0;
        politics = 0;
        sum = 0;
    }
    Arts(int t, string n, char g, T *p, T s)
    {
        id = t;
        name = n;
        gender = g;
        english = p[0];
        chinese = p[1];
        maths = p[2];
        geography = p[3];
        history = p[4];
        politics = p[5];
        sum = s;
    }

private:
    int id;
    string name;
    char gender;
    T english;
    T chinese;
    T maths;
    T geography;
    T history;
    T politics;
    T sum;
};

template <typename T>
class Combined
{
public:
    Combined()
    {
        id = 0;
        name = "Unknown";
        gender = 'U';
        english = 0;
        chinese = 0;
        maths = 0;
        opt1 = 0;
        opt2 = 0;
        opt3 = 0;
        sum = 0;
    }
    Combined(int t, string n, char g, T *p, T s)
    {
        id = t;
        name = n;
        gender = g;
        english = p[0];
        chinese = p[1];
        maths = p[2];
        opt1 = p[3];
        opt2 = p[4];
        opt3 = p[5];
        sum = s;
    }
    void Print()
    {
        cout << fixed << setprecision(0)
             << setw(10) << id
             << setw(10) << name
             << setw(10) << gender
             << fixed << setprecision(2)
             << setw(10) << english
             << setw(10) << chinese
             << setw(10) << maths
             << setw(10) << opt1
             << setw(10) << opt2
             << setw(10) << opt3
             << setw(10) << sum
             << endl;
    }
    double GetSum()
    {
        return sum;
    }
    double GetEnglish()
    {
        return english;
    }
    double GetChinese()
    {
        return chinese;
    }
    double GetMaths()
    {
        return maths;
    }

private:
    int id;
    string name;
    char gender;
    T english;
    T chinese;
    T maths;
    T opt1;
    T opt2;
    T opt3;
    T sum;
};

bool cmp(Combined<double> A, Combined<double> B)
{
    if (A.GetSum() != B.GetSum())
    {
        return A.GetSum() > B.GetSum();
    }
    else
    {
        if (A.GetEnglish() != B.GetEnglish())
        {
            return A.GetEnglish() > B.GetEnglish();
        }
        else
        {
            if (A.GetChinese() != B.GetChinese())
            {
                return A.GetChinese() > B.GetChinese();
            }
            else
            {
                if (A.GetMaths() != B.GetMaths())
                {
                    return A.GetMaths() > B.GetMaths();
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}

int main()
{
    Science<double> science[50];
    Arts<double> arts[50];
    Combined<double> cbn[100];

    int id = 0;
    string name = "Unknown";
    char gender = 'U';
    double s[6] = {0};
    double total = 0;

    int combinedCounter = 0;

    cout << "SCIENCE: \n"
         << setw(10) << "ID"
         << setw(10) << "NAME"
         << setw(10) << "GENDER"
         << setw(10) << "ENGLISH"
         << setw(10) << "CHINESE"
         << setw(10) << "MATHS"
         << setw(10) << "PHYSICS"
         << setw(10) << "CHEMISTRY"
         << setw(10) << "BIOLOGY"
         << setw(10) << "TOTAL"
         << endl;
    int scienceCounter = 0;

    ifstream infile1("ScienceStudent.txt", ios::in);
    infile1.seekg(0, ios::beg);
    while ((infile1 >> id) && scienceCounter < 5)
    {
        infile1 >> name >> gender >> s[0] >> s[1] >> s[2] >> s[3] >> s[4] >> s[5];
        total = accumulate(s, s + 6, 0);
        cout << fixed << setprecision(0)
             << setw(10) << id
             << setw(10) << name
             << setw(10) << gender
             << fixed << setprecision(2)
             << setw(10) << s[0]
             << setw(10) << s[1]
             << setw(10) << s[2]
             << setw(10) << s[3]
             << setw(10) << s[4]
             << setw(10) << s[5]
             << setw(10) << total
             << endl;
        science[scienceCounter] = Science<double>(id, name, gender, s, total);
        cbn[combinedCounter] = Combined<double>(id, name, gender, s, total);
        scienceCounter++;
        combinedCounter++;
    }

    cout << "ARTS: \n"
         << setw(10) << "ID"
         << setw(10) << "NAME"
         << setw(10) << "GENDER"
         << setw(10) << "ENGLISH"
         << setw(10) << "CHINESE"
         << setw(10) << "MATHS"
         << setw(10) << "HISTORY"
         << setw(10) << "GEOGRAPHY"
         << setw(10) << "POLITICS"
         << setw(10) << "TOTAL"
         << endl;
    int artsCounter = 0;

    ifstream infile2("ArtsStudent.txt", ios::in);
    infile2.seekg(0, ios::beg);
    while ((infile2 >> id) && artsCounter < 5)
    {
        infile2 >> name >> gender >> s[0] >> s[1] >> s[2] >> s[3] >> s[4] >> s[5];
        total = accumulate(s, s + 6, 0);
        cout << fixed << setprecision(0)
             << setw(10) << id
             << setw(10) << name
             << setw(10) << gender
             << fixed << setprecision(2)
             << setw(10) << s[0]
             << setw(10) << s[1]
             << setw(10) << s[2]
             << setw(10) << s[3]
             << setw(10) << s[4]
             << setw(10) << s[5]
             << setw(10) << total
             << endl;
        arts[artsCounter] = Arts<double>(id, name, gender, s, total);
        cbn[combinedCounter] = Combined<double>(id, name, gender, s, total);
        artsCounter++;
        combinedCounter++;
    }

    sort(cbn, cbn + combinedCounter, cmp);

    cout << "COMBINED: \n"
         << setw(10) << "ID"
         << setw(10) << "NAME"
         << setw(10) << "GENDER"
         << setw(10) << "ENGLISH"
         << setw(10) << "CHINESE"
         << setw(10) << "MATHS"
         << setw(10) << "OPT1"
         << setw(10) << "OPT2"
         << setw(10) << "OPT3"
         << setw(10) << "TOTAL"
         << endl;

    fstream fin("student.dat", ios::out | ios::binary);
    fin.seekp(0, ios::beg);
    for (int i = 0; i < combinedCounter; i++)
    {
        cbn[i].Print();
        fin.write((char *)&cbn[i], sizeof(cbn[i]));
    }
}
