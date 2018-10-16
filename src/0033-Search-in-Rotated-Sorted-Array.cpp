/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand. (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 *
 * You are given a target value to search. If found in the array return its
 * index, otherwise return -1.
 *
 * You may assume no duplicate exists in the array.
 *
 * Your algorithm's runtime complexity must be in the order of O(log n).
 *
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 */

#include <iostream>
#include <vector>

using std::vector;

// Note: time complexity -- O(long n)
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        return binarySearch(nums, left, right, target);
    }

    int binarySearch(vector<int> &nums, int left, int right, int target) {
        if (right < left) return -1;
        int mid = (left + right) / 2;
        int leftVal = nums[left], rightVal = nums[right], midVal = nums[mid];
        int ret = -1, tempRet = -1;
        if (target == midVal) {
            return mid;
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
        return tempRet != -1 ? tempRet : ret;
    }
};

int main() {
    Solution s;
    static int testId = 1;

    vector<int> nums1{4, 5, 6, 7, 0, 1, 2}; int target1 = 0;
    vector<int> nums2{4, 5, 6, 7, 0, 1, 2}; int target2 = 3;
    vector<int> nums3{3, 1}; int target3 = 1;

    auto exeTest = [&](vector<int> &nums, int target) {
        std::cout << "Case " << testId << ": "
                << s.search(nums, target) << std::endl;
        ++testId;
    };

    exeTest(nums1, target1);
    exeTest(nums2, target2);
    exeTest(nums3, target3);
}