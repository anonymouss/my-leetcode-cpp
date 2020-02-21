/**
 * You are a professional robber planning to rob houses along a street. Each
 * house has a certain amount of money stashed. All houses at this place are
 * arranged in a circle. That means the first house is the neighbor of the last
 * one. Meanwhile, adjacent houses have security system connected and it will
 * automatically contact the police if two adjacent houses were broken into on
 * the same night. Given a list of non-negative integers representing the amount
 * of money of each house, determine the maximum amount of money you can rob
 * tonight without alerting the police.
 *
 * Example 1:
 * Input: [2,3,2]
 * Output: 3
 * Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money =
 * 2),              because they are adjacent houses.
 *
 * Example 2:
 * Input: [1,2,3,1]
 * Output: 4
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 *              Total amount you can rob = 1 + 3 = 4.
 */

#include "MyMisc.h"

#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
    int rob(std::vector<int> &nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        return std::max(rob_l(nums, 0, n - 1), rob_l(nums, 1, n));
    }

private:
    int rob_l(std::vector<int> &nums, int start, int end) {
        auto dp0 = 0, dp1 = 0, t = 0;
        for (auto i = start; i < end; ++i) {
            t = dp1;
            dp1 = std::max(dp0 + nums[i], dp1);
            dp0 = t;
        }
        return dp1;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> inputs{{2, 3, 2}, {1, 2, 3, 1}};

    for (auto &nums : inputs) {
        TestCount();
        std::cout << sln.rob(nums) << std::endl;
    }
}