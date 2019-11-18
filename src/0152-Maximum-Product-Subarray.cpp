/**
 * Given an integer array nums, find the contiguous subarray within an array (containing at least
 * one number) which has the largest product.
 *
 * Example 1:
 * Input: [2,3,-2,4]
 * Output: 6
 * Explanation: [2,3] has the largest product 6.
 *
 * Example 2:
 * Input: [-2,0,-1]
 * Output: 0
 * Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 */

#include "MyMisc.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

class Solution {
public:
    // static const int kNegativeInf = -std::numeric_limits<int>::infinity();
    static const int kNegativeInf = INT32_MIN;
    int maxProduct(std::vector<int>& nums) {
        int max = kNegativeInf;
        int imax = 1, imin = 1;
        for (const auto& e : nums) {
            if (e < 0) std::swap(imax, imin);
            imax = std::max(imax * e, e);
            imin = std::min(imin * e, e);
            max = std::max(max, imax);
        }
        return max;
    }
};

int main() {
    Solution sln;
    std::vector<std::vector<int>> inputs{{2, 3, -2, 4}, {-2, 0, -1}, {-2}};

    for (auto& nums : inputs) {
        TestCount();
        std::cout << sln.maxProduct(nums) << std::endl;
    }
}