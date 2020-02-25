/**
 * Given an array of integers, find out whether there are two distinct indices i and j in the array
 * such that the absolute difference between nums[i] and nums[j] is at most t and the absolute
 * difference between i and j is at most k.
 *
 * Example 1:
 * Input: nums = [1,2,3,1], k = 3, t = 0
 * Output: true
 *
 * Example 2:
 * Input: nums = [1,0,1,1], k = 1, t = 2
 * Output: true
 *
 * Example 3:
 * Input: nums = [1,5,9,1,5,9], k = 2, t = 3
 * Output: false
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdint>

class Solution {
public:
    bool containsNearbyAlmostDuplicate(std::vector<int> &nums, int k, int t) {
        std::map<int64_t, int> kmap;
        std::size_t left = 0;
        for (auto right = 0; right < nums.size(); ++right) {
            if (right - left > k) {
                kmap.erase(nums[left]);
                ++left;
            }
            auto found = kmap.lower_bound(static_cast<int64_t>(nums[right]) - t);
            if (found != kmap.end() && std::abs(found->first - nums[right]) <= t) {
                return true;
            }
            kmap[nums[right]] = right;
        }
        return false;
    }
};

struct Input {
    std::vector<int> nums;
    int k;
    int t;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{
        {{1, 2, 3, 1}, 3, 0}, {{1, 0, 1, 1}, 1, 2}, {{1, 5, 9, 1, 5, 9}, 2, 3},
        {{2147483647, -2147483647}, 1, 2147483647}
    };

    for (auto &input : inputs) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.containsNearbyAlmostDuplicate(input.nums, input.k, input.t) << std::endl;
    }
}