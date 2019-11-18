/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 * (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
 * Find the minimum element.
 * The array may contain duplicates.
 *
 * Example 1:
 * Input: [1,3,5]
 * Output: 1
 *
 * Example 2:
 * Input: [2,2,2,0,1]
 * Output: 0
 *
 * Note:
 * This is a follow up problem to Find Minimum in Rotated Sorted Array.
 * Would allow duplicates affect the run-time complexity? How and why?
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    int findMin(std::vector<int> &nums) {
        if (nums.empty()) return 0;
        auto litr = nums.begin();
        auto ritr = nums.end() - 1;
        auto min = *litr;
        while (litr < ritr) {
            if (*litr > *(litr + 1)) {
                min = *(litr + 1);
                break;
            }
            if (*ritr < *(ritr - 1)) {
                min = *ritr;
                break;
            }
            ++litr;
            --ritr;
        }
        return min;
    }
};

int main() {
    Solution sln;
    std::vector<std::vector<int>> inputs{{1, 3, 5}, {2, 2, 2, 0, 1}};

    for (auto &nums : inputs) {
        TestCount();
        std::cout << sln.findMin(nums) << std::endl;
    }
}