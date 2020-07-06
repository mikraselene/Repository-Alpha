/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */

// @lc code=start
class Solution
{
public:
    bool isValid(string s)
    {
        unordered_map<char, int> m{{'(', 1}, {'[', 2}, {'{', 3}, {')', 4}, {']', 5}, {'}', 6}};
        stack<char> a;
        for (int i = 0; i < s.size(); i++)
        {
            int temp = m[s[i]];
            if (temp >= 1 && temp <= 3)
            {
                a.push(s[i]);
            }
            else if (!a.empty() && m[a.top()] == temp - 3)
            {
                a.pop();
            }
            else
            {
                return 0;
            }
        }
        if (!a.empty())
        {
            return 0;
        }
        return 1;
    }
};
// @lc code=end
