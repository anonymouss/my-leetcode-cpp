/**
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Your goal is to reach the last index in the minimum number of jumps.
 *
 * Example:
 * Input: [2,3,1,1,4]
 * Output: 2
 * Explanation: The minimum number of jumps to reach the last index is 2.
 *     Jump 1 step from index 0 to 1, then 3 steps to the last index.
 *
 * Note:
 * You can assume that you can always reach the last index.
 */

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
// brute force... TLE
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.empty()) return 0;
        int size = nums.size();
        vector<int> jumps(size, 0);
        for (int i = 1; i < size; ++i) {
            int tmpJumpMin = size; // a big value
            for (int j = 0; j < i; ++j) {
                if (nums[j] + j >= i) {
                    int tmpJump = jumps[j] + 1;
                    tmpJumpMin = tmpJumpMin < tmpJump ? tmpJumpMin : tmpJump;
                }
            }
            jumps[i] = tmpJumpMin;
        }
        return jumps[size - 1];
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    int jump(vector<int> &nums) {
        if (nums.empty()) return 0;
        int start = 0, end = 0, jumps = 0;
        while (end < nums.size() - 1) {
            int farthest = end;
            for (int i = start; i <= end; ++i) {
                if (i + nums[i] > farthest)
                    farthest = i + nums[i];
            }
            start = end + 1;
            end = farthest;
            ++jumps;
        }
        return jumps;
    }
};
#elif (COMPILE_VERSION == 2)
// TLE
class Solution {
public:
    int jump(vector<int> &nums) {
        if (nums.empty()) return 0;
        int jumps = 0, latsPos = nums.size() - 1;
        while(latsPos > 0) {
            for (int i = 0; i < latsPos; ++i) {
                if (i + nums[i] >= latsPos) {
                    latsPos = i;
                    ++jumps;
                    break;
                }
            }
        }
        return jumps;
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> numsVec{
        {2, 3, 1, 1, 4}
    };

    for (auto &nums : numsVec) {
        auto jumps = s.jump(nums);
        std::cout << "Case " << testId++ << ": " << jumps << std::endl;
    }
}