/**
 * Given an array nums, write a function to move all 0's to the end of it while maintaining the
 * relative order of the non-zero elements.
 * Example:
 *
 * Input: [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 *
 * Note:
 * You must do this in-place without making a copy of the array.
 * Minimize the total number of operations.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    void moveZeroes(std::vector<int> &nums) {
        auto len = nums.size();
        int iz = 0, in = 0;
        while (iz < len - 1 && in < len) {
            if (nums[iz] != 0) {
                ++iz;
                continue;
            }
            if (iz == len) break;
            in = (iz + 1) > in ? (iz + 1) : in;
            while (in < len && nums[in] == 0) {
                ++in;
            }
            if (in == len) break;
            if (in == len - 1 && nums[in] == 0) break;
            nums[iz] = nums[in];
            nums[in] = 0;
        }

    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    void moveZeroes(std::vector<int> &nums) {
        for (int lastNonZeroFoundAt = 0, cur = 0; cur < nums.size(); cur++) {
            if (nums[cur] != 0) {
                std::swap(nums[lastNonZeroFoundAt++], nums[cur]);
            }
        }
    }
};
#endif

int main() {
    Solution sln;

    std::vector<std::vector<int>> inputs{{0, 1, 0, 3, 12}};

    auto disp = [](const std::vector<int> &nums) {
        for (const auto &n : nums) std::cout << n << ", ";
        std::cout << std::endl;
    };

    for (auto &nums : inputs) {
        sln.moveZeroes(nums);
        disp(nums);
    }
}