/**
 * Given an array with n objects colored red, white or blue, sort them in-place so that objects of
 * the same color are adjacent, with the colors in the order red, white and blue.
 * Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
 * Note: You are not suppose to use the library's sort function for this problem.
 *
 * Example:
 * Input: [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 *
 * Follow up:
 * - A rather straight forward solution is a two-pass algorithm using counting sort.
 * - First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total
 *   number of 0's, then 1's and followed by 2's.
 * - Could you come up with a one-pass algorithm using only constant space?
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::swap;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        int i = l;
        while (i <= r) {
            if (nums[i] == 0) {
                // move 0 to the left
                swap(nums[l], nums[i]);
                while (nums[l] == 0) ++l; // skip 0s in the left
                i = l;
            } else if (nums[i] == 2) {
                // move 2 to the right
                swap(nums[r], nums[i]);
                while (nums[r] == 2) --r; // skip 2s in the right
            } else {
                // skip 1
                ++i;
            }
        }
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> inputs{
        {2, 0, 2, 1, 1, 0},
        {2, 0, 2, 1, 2, 0, 1, 0}
    };

    for (auto &nums : inputs) {
        s.sortColors(nums);
        std::cout << "Case " << testId++ << ": [";
        for (const auto &num : nums)
            std::cout << num << ", ";
        std::cout << "]" << std::endl;
    }
}