/**
 * Given an integer array nums, find the contiguous subarray (containing at least one number) which
 * has the largest sum and return its sum.
 *
 * Example:
 * Input: [-2,1,-3,4,-1,2,1,-5,4],
 * Output: 6
 * Explanation: [4,-1,2,1] has the largest sum = 6.
 *
 * Follow up: If you have figured out the O(n) solution, try coding another solution using the
 * divide and conquer approach, which is more subtle.
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        int sum = 0, max = nums[0], i = 0;
        // if the leading contiguous numbers are negative, find the max one
        for (; i < nums.size(); ++i) {
            if (nums[i] > 0) break;
            max = max > nums[i] ? max : nums[i];
        }
        // contains positive number, discard negative sum and restart from positive one
        for (; i < nums.size(); ++i) {
            sum += nums[i];
            if (sum < 0) sum  = 0;
            else max = sum > max ? sum : max;
        }
        return max;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> inputs{
        {-2, 1, -3, 4, -1, 2, 1, -5, 4},
        {-1},
        {-2, -1}
    };

    for (auto &nums : inputs) {
        auto res = s.maxSubArray(nums);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}