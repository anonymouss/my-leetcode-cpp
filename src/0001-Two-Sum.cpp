/**
 * Given an array of integers, return indices of the two numbers such that they
 * add up to a specific target.
 *
 * You may assume that each input would have exactly one solution, and you may
 * not use the same element twice.
 *
 * Example:
 *
 * Given nums = [2, 7, 11, 15], target = 9,
 *
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> uMap;
        auto size = nums.size();
        for (auto i = 0; i < size; ++i) {
            auto val = target - nums[i];
            if (uMap.find(val) != uMap.end()) {
                return {uMap[val], i};
            }
            uMap.emplace(nums[i], i);
        }
    }
};

int main() {
    vector<int> nums{2, 7, 11, 15};
    int target = 9;

    Solution solution;
    auto res = solution.twoSum(nums, target);

    std::cout << "[" << res[0] << ", " << res[1] << "]" << std::endl;
}