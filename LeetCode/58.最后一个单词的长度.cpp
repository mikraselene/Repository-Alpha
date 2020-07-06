/*
 * @lc app=leetcode.cn id=58 lang=cpp
 *
 * [58] 最后一个单词的长度
 */

// @lc code=start
class Solution
{
public:
    int lengthOfLastWord(string s)
    {
        auto pos = s.find_last_of(' ');
        while (pos == s.size() - 1)
        {
            if (s.empty())
            {
                return 0;
            }
            s.erase(pos);
            pos = s.find_last_of(' ');
        }
        if (s.find(" ") == string::npos)
        {
            return s.size();
        }
        else
        {
            return s.size() - pos - 1;
        }
    }
};
// @lc code=end
