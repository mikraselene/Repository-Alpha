#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    bool flag = 1;
    vector<string> code;
    string temp;
    while (getline(cin, temp) && temp != "END")
    {
        if (temp == "/*")
        {
            flag = 0;
        }
        if (temp == "*/")
        {
            flag = 1;
        }
        if (flag == 1 && temp != "*/")
        {
            if (temp.find("//") != temp.npos)
            {
                temp.erase(temp.find("//"), temp.size());
            }
            code.push_back(temp);
        }
    }
    vector<string>::iterator it;
    for (it = code.begin(); it != code.end(); it++)
    {
        cout << *it << endl;
    }
}