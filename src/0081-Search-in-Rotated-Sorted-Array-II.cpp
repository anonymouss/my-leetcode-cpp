/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 * (i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
 * You are given a target value to search. If found in the array return true, otherwise return false.
 *
 * Example 1:
 * Input: nums = [2,5,6,0,0,1,2], target = 0
 * Output: true
 *
 * Example 2:
 * Input: nums = [2,5,6,0,0,1,2], target = 3
 * Output: false
 *
 * Follow up:
 * This is a follow up problem to Search in Rotated Sorted Array, where nums may contain duplicates.
 * Would this affect the run-time complexity? How and why?
 */

#include "../utils/MyMisc.h"
#include "../utils/MyClock.h"

#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    bool search(vector<int>& nums, int target) {
#ifdef DEBUG
        MyClock<MY_MS> myClock("BinSearch");
#endif
        int left = 0, right = nums.size() - 1;
        return binarySearch(nums, left, right, target);
    }

    bool binarySearch(vector<int> &nums, int left, int right, int target) {
        if (right < left) return false;
        int mid = (left + right) / 2;
        int leftVal = nums[left], rightVal = nums[right], midVal = nums[mid];
        bool ret = false, tempRet = false;
        if (target == midVal) {
            return true;
        } else if (target < midVal) {
            ret = binarySearch(nums, left, mid - 1, target);
            if (target <= rightVal) {
                tempRet = binarySearch(nums, mid + 1, right, target);
            }
        } else {
            ret = binarySearch(nums, mid + 1, right, target);
            if (target >= leftVal) {
                tempRet = binarySearch(nums, left, mid - 1, target);
            }
        }
        return tempRet || ret;
    }
};
#elif (COMPILE_VERSION == 1)
// faster than approach 1
class Solution {
public:
    bool search(vector<int>& nums, int target) {
#ifdef DEBUG
        MyClock<MY_MS> myClock("Traverse");
#endif
        for (auto &n : nums) {
            if (n == target) return true;
        }
        return false;
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<pair<vector<int>, int>> inputs{
        {
            {2, 5, 6, 0, 0, 1, 2},
            0
        },
        {
            {2, 5, 6, 0, 0, 1, 2},
            3
        },
        {
            {6, 7, 8, 8, 9, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 1, 2, 3, 3, 4, 5},
            5
        }
    };

    for (auto &p : inputs) {
        auto exist = s.search(p.first, p.second);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << exist << std::endl;
    }
}