#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

struct student //global structure variable
{              //3 basic information
    string number;
    char name[20];
    double score[3];
};
student stu[10]; //10 students in array

int main()
{
    void inputdata(student stu[]), caculate(student stu[]),
        findmax(student stu[]), dispstu(student stu[]); //declare functions
    inputdata(stu);                                     //call input function
    cout << "The examination results are as follows" << endl;
    caculate(stu); //call average score calculating function
    cout << endl;
    cout << "Students with the highest scores "
         << "in single subject are as follows" << endl;
    cout << " SUBJECT  "
         << "  STUDENT "
         << "     CHI "
         << "    MAT "
         << "    ENG "
         << "    AVE" << endl;
    findmax(stu); //call highest score finding function
    dispstu(stu); //call print function
    return 0;
}
//define each function
void inputdata(student stu[])
{
    ifstream infile("data.txt");
    if (!infile) //fail to open
        cout << "Open Error!" << endl;
    else //input information from the file
        for (int i = 0; i < 10; i++)
        {
            infile >> stu[i].number;
            infile >> stu[i].name;
            for (int j = 0; j < 3; j++)
                infile >> stu[i].score[j];
        }
    infile.close(); //close file
}

void caculate(student stu[])
{
    double sum[3] = {0.0}, aver[3];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 3; j++)
            sum[j] += stu[i].score[j]; //add all
    for (int k = 0; k < 3; k++)
        aver[k] = sum[k] / 10; //average
    cout << "The average score of Chinese,Maths,English is: "
         << aver[0] << "  " << aver[1] << "  " << aver[2] << endl;
}

double maxscore[3];                   //highest score
int maxnum[3] = {0};                  //highest index
double sumper[3] = {0.0}, averper[3]; //personal score

void findmax(student stu[])
{
    for (int i = 0; i < 3; i++)
    {
        maxscore[i] = stu[0].score[i];
        for (int j = 1; j < 10; j++) //compare
        {
            if (stu[j].score[i] > maxscore[i])
            {
                maxscore[i] = stu[j].score[i];
                maxnum[i] = j; //save index
            }
        }
    }
    for (int k1 = 0; k1 < 3; k1++)
    {
        for (int k2 = 0; k2 < 3; k2++)
            sumper[k1] += stu[maxnum[k1]].score[k2]; //add
        averper[k1] = sumper[k1] / 3.0;
        //cout << averper[k1] << endl; //personal average
    }
}

void dispstu(student stu[])
{
    //findmax(stu);
    string subject[] = {"Chinese", "Maths", "English"};
    for (int i = 0; i < 3; i++)
    { //print
        cout << setw(8) << subject[i] << "   " << stu[maxnum[i]].number << " "
             << setw(5) << stu[maxnum[i]].name;
        for (int j = 0; j < 3; j++)
            cout << setw(8) << stu[maxnum[i]].score[j];
        cout << setw(8) << averper[i];
        cout << endl;
    }
}
