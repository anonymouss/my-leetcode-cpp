/**
 * Given a sorted array and a target value, return the index if the target is
 * found. If not, return the index where it would be if it were inserted in order.
 *
 * You may assume no duplicates in the array.
 *
 * Example 1:
 * Input: [1,3,5,6], 5
 * Output: 2
 *
 * Example 2:
 * Input: [1,3,5,6], 2
 * Output: 1
 *
 * Example 3:
 * Input: [1,3,5,6], 7
 * Output: 4
 *
 * Example 4:
 * Input: [1,3,5,6], 0
 * Output: 0
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    // silly problem... bin search is also applicable
    int searchInsert(vector<int>& nums, int target) {
        if (nums.empty()) return 0;
        int size = nums.size();
        for (int i = 0; i < size; ++i) {
            if (nums[i] >= target)
                return i;
        }
        return size;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<int> nums1{1, 3, 5, 6}; int target1 = 5;
    vector<int> nums2{1, 3, 5, 6}; int target2 = 2;
    vector<int> nums3{1, 3, 5, 6}; int target3 = 7;
    vector<int> nums4{1, 3, 5, 6}; int target4 = 0;

    auto exeTest = [&](vector<int> &nums, int target) {
        std::cout << "Case " << testId << ": "
                    << s.searchInsert(nums, target) << std::endl;
        ++testId;
    };

    exeTest(nums1, target1);
    exeTest(nums2, target2);
    exeTest(nums3, target3);
    exeTest(nums4, target4);
}