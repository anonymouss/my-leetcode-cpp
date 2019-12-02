/**
 * Given an array of integers that is already sorted in ascending order, find two numbers such that
 * they add up to a specific target number.
 * The function twoSum should return indices of the two numbers such that they add up to the target,
 * where index1 must be less than index2.
 * 
 * Note:
 * Your returned answers (both index1 and index2) are not zero-based.
 * You may assume that each input would have exactly one solution and you may not use the same
 * element twice.
 * 
 * Example:
 * Input: numbers = [2,7,11,15], target = 9
 * Output: [1,2]
 * Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <iostream>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int> &numbers, int target) {
        std::unordered_map<int, int> records;
        for (int i = 0; i < numbers.size(); ++i) {
            auto other = target - numbers[i];
            if (records.count(other) != 0) {
                return {records[other], i + 1};
            }
            records[numbers[i]] = i + 1;
        }
        return {};
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> inputs{{2, 7, 11, 15}};
    std::vector<int> targets{9};

    for (auto i = 0; i < inputs.size(); ++i) {
        TestCount();
        auto sum = sln.twoSum(inputs[i], targets[i]);
        std::cout << "[";
        if (!sum.empty()) std::cout << sum[0] << ", " << sum[1];
        std::cout << "]" << std::endl;
    }
}