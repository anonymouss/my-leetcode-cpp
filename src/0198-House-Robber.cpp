/**
 * You are a professional robber planning to rob houses along a street. Each house has a certain
 * amount of money stashed, the only constraint stopping you from robbing each of them is that
 * adjacent houses have security system connected and it will automatically contact the police if
 * two adjacent houses were broken into on the same night.
 * Given a list of non-negative integers representing the amount of money of each house, determine
 * the maximum amount of money you can rob tonight without alerting the police.
 *
 * Example 1:
 * Input: [1,2,3,1]
 * Output: 4
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 *              Total amount you can rob = 1 + 3 = 4.
 *
 * Example 2:
 * Input: [2,7,9,3,1]
 * Output: 12
 * Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
 *              Total amount you can rob = 2 + 9 + 1 = 12.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(std::vector<int> &nums) {
        int dp_1 = 0, dp_2 = 0;
        for (const auto &n : nums) {
            auto tmp = dp_1;
            dp_1 = std::max(dp_2 + n, dp_1);
            dp_2 = tmp;
        }
        return dp_1;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> numsv{
        {1, 2, 3, 1},
        {2, 7, 9, 3, 1}
    };

    for (auto &nums : numsv) {
        TestCount();
        std::cout << sln.rob(nums) << std::endl;
    }
}