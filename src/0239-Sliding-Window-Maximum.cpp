/**
 * Given an array nums, there is a sliding window of size k which is moving from the very left of
 * the array to the very right. You can only see the k numbers in the window. Each time the sliding
 * window moves right by one position. Return the max sliding window.
 *
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
 * Output: [3,3,5,5,6,7] 
 * Explanation: 
 * Window position                Max
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       3
 *  1 [3  -1  -3] 5  3  6  7       3
 *  1  3 [-1  -3  5] 3  6  7       5
 *  1  3  -1 [-3  5  3] 6  7       5
 *  1  3  -1  -3 [5  3  6] 7       6
 *  1  3  -1  -3  5 [3  6  7]      7
 *
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.
 * Follow up:
 * Could you solve it in linear time?
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <deque>

class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
        if (k == 0 || nums.empty()) return {};
        std::vector<int> maxs;
        std::deque<int> windowIndexes;
        for (auto i = 0; i < k; ++i) {
            while (!windowIndexes.empty() && nums[i] > nums[windowIndexes.back()]) {
                windowIndexes.pop_back();
            }
            windowIndexes.emplace_back(i);
        }
        maxs.emplace_back(nums[windowIndexes.front()]);
        for (auto i = k; i < nums.size(); ++i) {
            if (!windowIndexes.empty() && windowIndexes.front() <= i - k) {
                windowIndexes.pop_front();
            }
            while (!windowIndexes.empty() && nums[i] > nums[windowIndexes.back()]) {
                windowIndexes.pop_back();
            }
            windowIndexes.emplace_back(i);
            maxs.emplace_back(nums[windowIndexes.front()]);
        }
        return maxs;
    }
};

struct Input {
    std::vector<int> nums;
    int k;

    Input(std::vector<int> &&_nums, int _k) : nums(std::move(_nums)), k(_k) {}
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{{1, 3, -1, -3, 5, 3, 6, 7}, 3}};

    auto print_v = [](const std::vector<int> &maxs) {
        for (auto &max : maxs) std::cout << max << ", ";
        std::cout << std::endl;
    };

    for (auto &input : inputs) {
        TestCount();
        print_v(sln.maxSlidingWindow(input.nums, input.k));
    }
}