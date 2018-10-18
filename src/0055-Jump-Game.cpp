/**
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Determine if you are able to reach the last index.
 *
 * Example 1:
 * Input: [2,3,1,1,4]
 * Output: true
 * Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 *
 * Example 2:
 * Input: [3,2,1,0,4]
 * Output: false
 * Explanation: You will always arrive at index 3 no matter what. Its maximum
 *              jump length is 0, which makes it impossible to reach the last
 *              index.
 */

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERSION 2

#if (COMPILE_VERSION == 0)
// brute force
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.empty()) return false;
        int size = nums.size();
        vector<bool> res(size, false);
        res[0] = true;
        for (int i = 1; i < size; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] >= (i - j) && res[j]) {
                    res[i] = true;
                    break;
                }
            }
        }
        return res[size - 1];
    }
};
#elif (COMPILE_VERSION == 1)
// back tracking
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// this solution will be TLE
class Solution {
public:
    bool canJump(vector<int> &nums) {
        return canJumpFromPosition(nums, 0);
    }

    bool canJumpFromPosition(vector<int> &nums, int position) {
        if (position == nums.size() - 1) return true;
        int furthestJump = MIN(position + nums[position], nums.size() - 1);
        // for (int pos = position + 1; pos <= furthestJump; ++pos) {
        for (int pos = furthestJump; pos > position; --pos) {
            if (canJumpFromPosition(nums, pos)) return true;
        }
        return false;
    }
};
#elif (COMPILE_VERSION == 2)
class Solution {
public:
    bool canJump(vector<int> &nums) {
        if (nums.empty()) return false;
        int lastPos = nums.size() - 1;
        for (int pos = nums.size() - 1; pos >= 0; --pos) {
            if (pos + nums[pos] >= lastPos)
                lastPos = pos;
        }
        return lastPos == 0;
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> numsVec{
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4},
        {2, 0},
        {1, 0, 1, 0},
        {2, 1, 0, 0},
        {2, 0, 0}
    };

    for (auto &nums : numsVec) {
        auto res = s.canJump(nums);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}