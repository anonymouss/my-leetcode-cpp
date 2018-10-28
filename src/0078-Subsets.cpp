/**
 * Given a set of distinct integers, nums, return all possible subsets (the power set).
 * Note: The solution set must not contain duplicate subsets.
 *
 * Example:
 * Input: nums = [1,2,3]
 * Output:
 * [
 *   [3],
 *   [1],
 *   [2],
 *   [1,2,3],
 *   [1,3],
 *   [2,3],
 *   [1,2],
 *   []
 * ]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res{{}}; // always contain an empty subset
        if (nums.empty()) return res;

        sort(nums.begin(), nums.end());

        for (auto &n : nums) {
            int resSize = res.size();
            for (int i = 0; i < resSize; ++i) {
                // add new val to all subsets, but keep original subset, that means here should
                // use copy, not reference
                auto v = res[i];
                v.emplace_back(n);
                res.emplace_back(v);
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> numsVec{
        {1, 2, 3}
    };

    for (auto &nums : numsVec) {
        auto res = s.subsets(nums);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &vec : res) {
            std::cout << "    [";
            for (const auto &n : vec)
                std::cout << n << ", ";
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    }
}