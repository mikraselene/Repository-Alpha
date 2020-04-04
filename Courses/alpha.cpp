#include <iostream>
using namespace std;

int sumEnglish = 0;
int sumChinese = 0;
int sumMaths = 0;
int num = 0;

class Student
{
public:
    Student()
    {
        studentId = 0;
        name = "Unknown";
        gender = 'U';
        subjectEnglish = 0;
        subjectChinese = 0;
        subjectMaths = 0;
        num++;
    }
    Student(Student &a)
    {
        this->studentId = a.studentId;
        this->name = a.name;
        this->gender = a.gender;
        this->subjectEnglish = a.subjectEnglish;
        this->subjectChinese = a.subjectChinese;
        this->subjectMaths = a.subjectMaths;
        sumEnglish += a.subjectEnglish;
        sumChinese += a.subjectChinese;
        sumMaths += a.subjectMaths;
    }
    Student(long id, string n, char gd, int eng, int chn, int mth)
    {
        studentId = id;
        name = n;
        gender = gd;
        subjectEnglish = eng;
        subjectChinese = chn;
        subjectMaths = mth;
        sumEnglish += eng;
        sumChinese += chn;
        sumMaths += mth;
        num++;
    }
    void PrintStudent()
    {
        printf("学号: %ld \t", studentId);
        printf("姓名: %s \t", name.c_str());
        printf("性别: %c \t", gender);
        printf("英语: %d \t", subjectEnglish);
        printf("语文: %d \t", subjectChinese);
        printf("数学: %d \t", subjectMaths);
        printf("\n");
    }
    double EnglishAvg()
    {
        return (sumEnglish * 1.0) / num;
    }
    double ChineseAvg()
    {
        return (sumChinese * 1.0) / num;
    }
    double MathsAvg()
    {
        return (sumMaths * 1.0) / num;
    }
    void PrintAvg()
    {
        printf("英语的平均分是 %lg\n", EnglishAvg());
        printf("语文的平均分是 %lg\n", ChineseAvg());
        printf("数学的平均分是 %lg\n", MathsAvg());
    }

private:
    long studentId;
    string name;
    char gender;
    int subjectEnglish;
    int subjectChinese;
    int subjectMaths;
};

int main()
{
    Student student1(1001, "Li Hua", 'F', 91, 71, 81);
    Student student2(1002, "He Xiao", 'M', 92, 72, 82);
    Student student3 = student1;
    Student student4;
    Student avg;
    avg.PrintAvg();
    student1.PrintStudent();
    student2.PrintStudent();
    student3.PrintStudent();
    student4.PrintStudent();
    printf("\n");
}