/**
 * Given an array of n positive integers and a positive integer s, find the minimal length of a
 * contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.
 *
 * Example: 
 * Input: s = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: the subarray [4,3] has the minimal length under the problem constraint.
 * Follow up:
 * If you have figured out the O(n) solution, try coding another solution of which the time
 * complexity is O(n log n). 
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

class Solution {
public:
    int minSubArrayLen(int s, std::vector<int> &nums) {
        auto len = nums.size();
        if (len == 0) return 0;
        auto ans = INT32_MAX;
        std::vector<int> sums(len + 1, 0);
        for (auto i = 1; i <= len; ++i) {
            sums[i] = sums[i - 1] + nums[i - 1];
        }
        for (auto i = 1; i <= len; ++i) {
            auto target = s + sums[i - 1];
            auto bound = std::lower_bound(sums.begin(), sums.end(), target);
            if (bound != sums.end()) {
                ans = std::min(ans, static_cast<int>(bound - (sums.begin() + i - 1)));
            }
        }
        return (ans != INT32_MAX) ? ans : 0;
    }
};

struct Input {
    int s;
    std::vector<int> nums;
    Input(int _s, std::vector<int> _nums) : s(_s), nums(_nums) {}
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{7, {2, 3, 1, 2, 4, 3}}};

    for (auto &input : inputs) {
        TestCount();
        std::cout << sln.minSubArrayLen(input.s, input.nums) << std::endl;
    }
}