#include <iostream>
#include <stack>
using namespace std;
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		string s;
		stack<char> st;
		cin >> s;
		while (!st.empty())
		{
			st.pop();
		}
		int len = s.size();
		int flag = 1;
		for (int i = 0; i < len; i++)
		{
			if (s[i] == '(')
			{
				st.push(s[i]);
			}
			else
			{
				if (st.empty())
				{
					flag = 0;
					break;
				}
				char t = st.top();
				st.pop();
				if (t == ')')
				{
					flag = 0;
					break;
				}
			}
		}
		if (!st.empty())
		{
			flag = 0;
		}
		if (flag == 1)
		{
			cout << "TRUE" << endl;
		}
		else
		{
			cout << "FALSE" << endl;
		}
	}
}