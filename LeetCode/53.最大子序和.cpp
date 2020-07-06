/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子序和
 */

// @lc code=start
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int pre = 0;
        int maxAns = nums[0];
        for (int i = 0; i < nums.size(); i++)
        {
            pre = max(pre + nums[i], nums[i]);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};
// @lc code=end
