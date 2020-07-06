/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hashMap;
        for (int i = 0; i < nums.size(); i++)
        {
            if (hashMap.count(target - nums[i]))
            {
                return {hashMap[target - nums[i]], i};
            }
            hashMap[nums[i]] = i;
        }
        return {};
    }
};
// @lc code=end
