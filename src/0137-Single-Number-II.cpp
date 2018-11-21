/**
 * Given a non-empty array of integers, every element appears three times except for one, which
 * appears exactly once. Find that single one.
 *
 * Note: Your algorithm should have a linear runtime complexity. Could you implement it without
 * using extra memory?
 *
 * Example 1:
 * Input: [2,2,3,2]
 * Output: 3
 *
 * Example 2:
 * Input: [0,1,0,1,0,1,99]
 * Output: 99
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int once = 0, twice = 0, thirce = 0;
        for (auto &num : nums) {
            twice |= once & num;
            once ^= num;
            thirce = twice & once;
            once &= ~thirce;
            twice &= ~thirce;
        }
        return once;
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int once = 0, twice = 0;
        for (auto &num : nums) {
            once = (once ^ num) & ~twice;
            twice = (twice ^ num) & ~once;
        }
        return once;
    }
};
#endif

int main() {
    Solution s;

    vector<vector<int>> numsVec{
        {2, 2, 3, 2},
        {0, 1, 0, 1, 0, 1, 99}
    };

    for (auto &nums : numsVec) {
        TestCount();
        auto single = s.singleNumber(nums);
        std::cout << single << std::endl;
    }
}