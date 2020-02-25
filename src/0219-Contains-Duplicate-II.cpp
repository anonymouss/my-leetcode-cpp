/**
 * Given an array of integers and an integer k, find out whether there are two distinct indices i
 * and j in the array such that nums[i] = nums[j] and the absolute difference between i and j is at
 * most k.
 *
 * Example 1:
 * Input: nums = [1,2,3,1], k = 3
 * Output: true
 *
 * Example 2:
 * Input: nums = [1,0,1,1], k = 1
 * Output: true
 *
 * Example 3:
 * Input: nums = [1,2,3,1,2,3], k = 2
 * Output: false
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int> &nums, int k) {
        std::unordered_set<int> hashTable;
        int n = nums.size();
        if (k >= n - 1) {
            for (auto &num : nums) {
                if (hashTable.count(num) != 0) return true;
                hashTable.emplace(num);
            }
        } else {
            for (auto i = 0; i <= k; ++i) {
                if (hashTable.count(nums[i]) != 0) return true;
                hashTable.emplace(nums[i]);
            }
            for (auto i = k + 1; i < n; ++i) {
                auto pos = hashTable.find(nums[i - k - 1]);
                hashTable.erase(pos);
                if (hashTable.count(nums[i]) != 0) return true;
                hashTable.emplace(nums[i]);
            }
        }
        return false;
    }
};

struct Input {
    std::vector<int> nums;
    int k;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{{1, 2, 3, 1}, 3}, {{1, 0, 1, 1}, 1}, {{1, 2, 3, 1, 2, 3}, 2}};

    for (auto &input : inputs) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.containsNearbyDuplicate(input.nums, input.k) << std::endl;
    }
}