/**
 * Given an unsorted integer array, find the smallest missing positive integer.
 *
 * Example 1:
 * Input: [1,2,0]
 * Output: 3
 *
 * Example 2:
 * Input: [3,4,-1,1]
 * Output: 2
 *
 * Example 3:
 * Input: [7,8,9,11,12]
 * Output: 1
 *
 * Note:
 * Your algorithm should run in O(n) time and uses constant extra space.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::swap;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if (nums.empty()) return 1;
        /**
         * The basic idea is to move elements (0 < lenght) to positions(index)
         * corresponding to their values. (the n-th element's value should
         * equals to n). Ignore negative values and values > lenght (actually,
         * if there is no value 1 in nums, the final return value should be 1).
         * After that, iterate through nums to find the first not-in-position
         * value, return position (index + 1).
         */
        for (int i = 0; i < nums.size(); ++i) {
            while (nums[i] > 0 && nums[i] <= nums.size()
                    && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        for (int i = 0; i < nums.size(); ++i)
            if (nums[i] != i + 1)
                return i + 1;
        return nums.size() + 1;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<int> nums1{1, 2, 0};
    vector<int> nums2{3, 4, -1, 1};
    vector<int> nums3{7, 8, 9, 11, 12};
    vector<int> nums4;
    vector<int> nums5{1};

    auto exeTest = [&](vector<int> &nums) {
        int res = s.firstMissingPositive(nums);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    };

    exeTest(nums1);
    exeTest(nums2);
    exeTest(nums3);
    exeTest(nums4);
    exeTest(nums5);
}