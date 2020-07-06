/*
 * @lc app=leetcode.cn id=13 lang=cpp
 *
 * [13] 罗马数字转整数
 */

// @lc code=start
class Solution
{
public:
    int romanToInt(string s)
    {
        int previous = Char2Int(s[0]);
        int sum = 0;
        for (int i = 1; i < s.size(); i++)
        {
            if (previous < Char2Int(s[i]))
            {
                sum -= previous;
            }
            else
            {
                sum += previous;
            }
            previous = Char2Int(s[i]);
        }
        sum += previous;
        return sum;
    }
    int Char2Int(char k)
    {
        switch (k)
        {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        }
        return 0;
    }
};
// @lc code=end
