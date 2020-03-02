/**
 * Given an array of numbers nums, in which exactly two elements appear only once and all the other
 * elements appear exactly twice. Find the two elements that appear only once.
 *
 * Example:
 * Input:  [1,2,1,3,2,5]
 * Output: [3,5]
 *
 * Note:
 * The order of the result is not important. So in the above example, [5, 3] is also correct.
 * Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <cstdint>

class Solution {
public:
    std::vector<int> singleNumber(std::vector<int> &nums) {
        uint32_t x = 0;
        for (auto &num : nums) {
            x ^= num;
        }
        std::vector<int> res, part1, part2;
        uint32_t bitOfHighestOne = 0;
        while (x) {
            ++bitOfHighestOne;
            x >>= 1;
        }
        auto mask = 1 << (bitOfHighestOne - 1);
        int num1 = 0, num2 = 0;
        for (auto &n : nums) {
            if (n & mask) {
                num1 ^= n;
            } else {
                num2 ^= n;
            }
        }
        res.emplace_back(num1);
        res.emplace_back(num2);
        return res;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> numsv{{1, 2, 1, 3, 2, 5}, {-1, 0}};

    auto print_v = [](const std::vector<int> nums) {
        for (const auto &n : nums) std::cout << n << ", ";
        std::cout << std::endl;
    };

    for (auto &nums : numsv) {
        TestCount();
        print_v(sln.singleNumber(nums));
    }
}