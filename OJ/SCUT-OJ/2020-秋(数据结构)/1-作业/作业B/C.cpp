#include <iostream>
#include <stack>
using namespace std;
int main()
{
    string s;
    while (cin >> s)
    {
        stack<char> st;
        while (!st.empty())
        {
            st.pop();
        }
        int len = s.size();
        int flag = 1;
        for (int i = 0; i < len; i++)
        {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[' ||
                s[i] == ')' || s[i] == '}' || s[i] == ']')
            {
                if (s[i] == '(' || s[i] == '{' || s[i] == '[')
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
                    if (s[i] == ')' && (t == '[' || t == '{'))
                    {
                        flag = 0;
                        break;
                    }
                    else if (s[i] == '}' && (t == '(' || t == '['))
                    {
                        flag = 0;
                        break;
                    }
                    else if (s[i] == ']' && (t == '{' || t == '('))
                    {
                        flag = 0;
                        break;
                    }
                }
            }
        }
        if (!st.empty())
        {
            flag = 0;
        }
        cout << flag << endl;
    }
}