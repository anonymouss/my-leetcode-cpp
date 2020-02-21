/**
 * Given an array of integers, find if the array contains any duplicates.
 * Your function should return true if any value appears at least twice in the array, and it should
 * return false if every element is distinct.
 *
 * Example 1:
 * Input: [1,2,3,1]
 * Output: true
 *
 * Example 2:
 * Input: [1,2,3,4]
 * Output: false
 *
 * Example 3:
 * Input: [1,1,1,3,3,4,3,2,4,2]
 * Output: true
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool containsDuplicate(std::vector<int> &nums) {
        std::unordered_set<int> hashTable;
        for (auto &n : nums) {
            if (hashTable.count(n) != 0) return true;
            hashTable.emplace(n);
        }
        return false;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> numsv{
        {1, 2, 3, 1}, {1, 2, 3, 4}, {1, 1, 1, 3, 3, 4, 3, 2, 4, 2}
    };

    for (auto &nums : numsv) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.containsDuplicate(nums) << std::endl;
    }
}