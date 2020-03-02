/**
 * Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is
 * missing from the array.
 *
 * Example 1:
 * Input: [3,0,1]
 * Output: 2
 *
 * Example 2:
 * Input: [9,6,4,2,3,5,7,0,1]
 * Output: 8
 *
 * Note:
 * Your algorithm should run in linear runtime complexity. Could you implement it using only
 * constant extra space complexity?
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    int missingNumber(std::vector<int> &nums) {
        int n = nums.size() + 1;
        auto sumExpected = (n - 1) * n / 2;
        auto sumReal = 0;
        for (auto &n : nums) {
            sumReal += n;
        }
        return sumExpected - sumReal;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> numsv{
        {3, 0, 1}, {9, 6, 4, 2, 3, 5, 7, 0, 1}
    };

    for (auto &nums : numsv) {
        TestCount();
        std::cout << sln.missingNumber(nums) << std::endl;
    }
}