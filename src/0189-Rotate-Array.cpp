/**
 * Given an array, rotate the array to the right by k steps, where k is non-negative.
 *
 * Example 1:
 * Input: [1,2,3,4,5,6,7] and k = 3
 * Output: [5,6,7,1,2,3,4]
 * Explanation:
 * rotate 1 steps to the right: [7,1,2,3,4,5,6]
 * rotate 2 steps to the right: [6,7,1,2,3,4,5]
 * rotate 3 steps to the right: [5,6,7,1,2,3,4]
 *
 * Example 2:
 * Input: [-1,-100,3,99] and k = 2
 * Output: [3,99,-1,-100]
 * Explanation: 
 * rotate 1 steps to the right: [99,-1,-100,3]
 * rotate 2 steps to the right: [3,99,-1,-100]
 *
 * Note:
 * Try to come up as many solutions as you can, there are at least 3 different ways to solve this
 * problem.
 * Could you do it in-place with O(1) extra space?
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    void rotate(std::vector<int> &nums, int k) {
        auto len = nums.size();
        k %= len;
        int count = 0;
        for (auto startPos = 0; count < len; ++startPos) {
            auto currentPos = startPos;
            auto currentVal = nums[currentPos];
            do {
                auto nextPos = (currentPos + k) % len;
                auto nextVal = nums[nextPos];
                nums[nextPos] = currentVal;
                currentPos = nextPos;
                currentVal = nextVal;
                ++count;
            } while(startPos != currentPos);
        }
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    void rotate(std::vector<int> &nums, int k) {
        k %= nums.size();
        std::reverse(std::begin(nums), std::end(nums));
        std::reverse(std::begin(nums), std::begin(nums) + k);
        std::reverse(std::begin(nums) + k, std::end(nums));
    }
};
#endif

int main() {
    Solution sln;

    std::vector<std::vector<int>> numsv{
        {1, 2, 3, 4, 5, 6, 7},
        {-1, -100, 3, 99}
    };
    std::vector<int> kv{3, 2};

    auto print_v = [](const std::vector<int> &v) {
        std::cout << "[";
        for (const auto &e : v) {
            std::cout << e << ", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto i = 0; i < numsv.size(); ++i) {
        TestCount();
        sln.rotate(numsv[i], kv[i]);
        print_v(numsv[i]);
    }
}