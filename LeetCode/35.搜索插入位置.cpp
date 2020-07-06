/*
 * @lc app=leetcode.cn id=35 lang=cpp
 *
 * [35] 搜索插入位置
 */

// @lc code=start
class Solution
{
public:
    int searchInsert(vector<int> &nums, int target)
    {
        if (!nums.size())
        {
            return 0;
        }
        if (nums[nums.size() - 1] < target)
        {
            return nums.size();
        }
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] < target)
            {
                lo = mid + 1;
            }
            else
            {
                hi = mid;
            }
        }
        return lo;
    }
};
// @lc code=end
