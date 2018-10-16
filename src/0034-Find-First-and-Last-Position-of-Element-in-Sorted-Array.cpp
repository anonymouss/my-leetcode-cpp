/**
 * Given an array of integers nums sorted in ascending order, find the starting
 * and ending position of a given target value.
 *
 * Your algorithm's runtime complexity must be in the order of O(log n).
 *
 * If the target is not found in the array, return [-1, -1].
 *
 * Example 1:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 *
 * Example 2:
 * Input: nums = [5,7,7,8,8,10], target = 6
 * Output: [-1,-1]
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        auto l = binarySearch(nums, left, right, target, true);
        if (l == -1) return {-1, -1};
        auto r = binarySearch(nums, l, right, target, false);
        return {l, r};
    }

    int binarySearch(vector<int> &nums, int left, int right,
                    int target, bool checkLeft) {
        if (right < left) return -1;
        int mid = (left + right) / 2;
        int leftVal = nums[left], rightVal = nums[right], midVal = nums[mid];
        if (midVal == target) {
            if (checkLeft) {
                if (mid == left || nums[mid - 1] < target) return mid;
                else return binarySearch(nums, left, mid - 1, target, checkLeft);
            } else {
                if (mid == right || nums[mid + 1] > target) return mid;
                else return binarySearch(nums, mid + 1, right, target, checkLeft);
            }
        } else if (midVal > target) {
            return binarySearch(nums, left, mid - 1, target, checkLeft);
        } else {
            return binarySearch(nums, mid + 1, right, target, checkLeft);
        }
    }
};

int main() {
    Solution s;
    static int testId = 1;

    vector<int> nums1{5, 7, 7, 8, 8, 10}; int target1 = 8;
    vector<int> nums2{5, 7, 7, 8, 8, 10}; int target2 = 6;

    auto exeTest = [&](vector<int> &nums, int target) {
        std::cout << "Case " << testId << ": [";
        auto vec = s.searchRange(nums, target);
        for (const auto &v : vec)
            std::cout << v << ", ";
        std::cout << "]" << std::endl;
    };

    exeTest(nums1, target1);
    exeTest(nums2, target2);
}