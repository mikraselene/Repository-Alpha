/*
 * @lc app=leetcode.cn id=67 lang=cpp
 *
 * [67] 二进制求和
 */

// @lc code=start
class Solution
{
public:
    string addBinary(string a, string b)
    {
        string ans;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int n = max(a.size(), b.size());
        int carry = 0;
        for (int i = 0; i < n; i++)
        {
            carry += i < a.size() ? (a[i] == '1') : 0;
            carry += i < b.size() ? (b[i] == '1') : 0;
            ans.push_back((carry % 2) ? '1' : '0');
            carry /= 2;
        }
        if (carry)
        {
            ans.push_back('1');
        }
        reverse(ans.begin(), ans.end());

        return ans;
    }
};
// @lc code=end
