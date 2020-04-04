#include <iostream>
#include <sstream>
#include <set>
using namespace std;
#define MAX_N 999
int main()
{
	string s;
	while (getline(cin, s) && s != "#")
	{
		istringstream strin(s);
		set<string> words;
		string temp;
		while (strin >> temp)
		{
			words.insert(temp);
		}
		int num = words.size();
		printf("%d\n", num);
	}
}