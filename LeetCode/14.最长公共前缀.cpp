/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] 最长公共前缀
 */

// @lc code=start
class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.size() == 0)
        {
            return "";
        }
        int lo = 0;
        int hi = min_element(strs.begin(), strs.end(),
                             [](string s, string t) { return s.size() < t.size(); })
                     ->size();
        while (lo < hi)
        {
            int mid = (hi - lo + 1) / 2 + lo;
            if (IsOK(strs, mid))
            {
                lo = mid;
            }
            else
            {
                hi = mid - 1;
            }
        }
        return strs[0].substr(0, lo);
    }
    bool IsOK(vector<string> strs, int cut)
    {
        string sub = strs[0].substr(0, cut);
        for (int i = 1; i < strs.size(); i++)
        {
            for (int j = 0; j < cut; j++)
            {
                if (sub[j] != strs[i][j])
                {
                    return 0;
                }
            }
        }
        return 1;
    }
};
// @lc code=end
