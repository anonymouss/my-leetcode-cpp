/**
 * Given a collection of integers that might contain duplicates, nums, return all possible subsets
 * (the power set).
 * Note: The solution set must not contain duplicate subsets.
 *
 * Example:
 * Input: [1,2,2]
 * Output:
 * [
 *   [2],
 *   [1],
 *   [1,2,2],
 *   [2,2],
 *   [1,2],
 *   []
 * ]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::find;
using std::sort;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res{{}};

        // actually, this line is unnecessary, below for-loop can handle it. but return directly
        // may reduce execution time since result is obvious for empty input
        if (nums.empty()) return res;

        sort(nums.begin(), nums.end());
        int lastN = nums[0], lastSize = 1;
        for (const auto &n : nums) {
            if (n != lastN) {
                lastN = n;
                lastSize = res.size();
            }
            int size = res.size();
            for (int i = size - lastSize; i < size; ++i) {
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

    vector<vector<int>> inputs{
        {1, 2, 2},
        {},
        {4, 4, 4, 1, 4}
    };

    for (auto &nums : inputs) {
        auto res = s.subsetsWithDup(nums);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &sub : res) {
            std::cout << "    [";
            for (const auto &e : sub) std::cout << e << ", ";
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    }
}