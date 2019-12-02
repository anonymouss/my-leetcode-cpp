/**
 * Given an array of size n, find the majority element. The majority element is the element that
 * appears more than ⌊ n/2 ⌋ times.
 * You may assume that the array is non-empty and the majority element always exist in the array.
 * 
 * Example 1:
 * Input: [3,2,3]
 * Output: 3
 * 
 * Example 2:
 * Input: [2,2,1,1,1,2,2]
 * Output: 2
 */

#include "MyMisc.h"

#include <vector>
#include <iostream>
#include <unordered_map>

class Solution {
public:
    int majorityElement(std::vector<int> &nums) {
        std::unordered_map<int, int> record;
        int threshold = nums.size() / 2;
        for (auto &n : nums) {
            record[n]++;
            if (record[n] > threshold) return n;
        }
        return 0;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> inputs{{3, 2, 3}, {2, 2, 1, 1, 1, 2, 2}};
    for (auto &nums : inputs) {
        TestCount();
        std::cout << sln.majorityElement(nums) << std::endl;
    }
}