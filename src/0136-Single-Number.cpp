/**
 * Given a non-empty array of integers, every element appears twice except for one. Find that single
 * one.
 * Note: Your algorithm should have a linear runtime complexity. Could you implement it without using
 * extra memory?
 *
 * Example 1:
 * Input: [2,2,1]
 * Output: 1
 *
 * Example 2:
 * Input: [4,1,2,1,2]
 * Output: 4
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int single = nums[0];
        for (int i = 1; i < nums.size(); ++i)
            single ^= nums[i];
        return single;
    }
};

int main() {
    Solution s;

    vector<vector<int>> numsVec{
        {2, 2, 1},
        {4, 1, 2, 1, 2}
    };

    for (auto &nums : numsVec) {
        TestCount();
        auto single = s.singleNumber(nums);
        std::cout << single << std::endl;
    }
}