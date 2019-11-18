/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 * (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
 * Find the minimum element.
 * You may assume no duplicate exists in the array.
 *
 * Example 1:
 * Input: [3,4,5,1,2]
 * Output: 1
 *
 * Example 2:
 * Input: [4,5,6,7,0,1,2]
 * Output: 0
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

    std::vector<std::vector<int>> inputs{{4, 5, 6, 7, 0, 1, 2}, {3, 4, 5, 1, 2}};

    for (auto &nums : inputs) {
        TestCount();
        std::cout << sln.findMin(nums) << std::endl;
    }
}