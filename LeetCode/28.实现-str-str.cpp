/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] 实现 strStr()
 */

// @lc code=start
class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        if (needle.empty())
        {
            return 0;
        }
        else
        {
            return haystack.find(needle);
        }
    }
};
// @lc code=end
