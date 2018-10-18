/**
 * Given a collection of distinct integers, return all possible permutations.
 *
 * Example:
 * Input: [1,2,3]
 * Output:
 *   [
 *     [1,2,3],
 *     [1,3,2],
 *     [2,1,3],
 *     [2,3,1],
 *     [3,1,2],
 *     [3,2,1]
 *   ]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty()) return res;
        sort(nums.begin(), nums.end());
        res.push_back(nums);
        while (nextPermute(nums))
            res.push_back(nums);
        return res;
    }

    bool nextPermute(vector<int> &nums) {
        int end = nums.size() - 1;
        for (int idx = end; idx > 0; --idx) {
            if (nums[idx] > nums[idx - 1]) {
                int i = end;
                while (nums[i] <= nums[idx - 1]) --i;
                auto val = nums[i];
                nums[i] = nums[idx - 1];
                nums[idx - 1] = val;
                int l = idx, r = end;
                while (l < r) {
                    auto t = nums[l];
                    nums[l] = nums[r];
                    nums[r] = t;
                    ++l; --r;
                }
                return true;
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> numsVec{
        {1, 2, 3},
        {5, 3, 2, 4, 1}
    };

    for (auto &nums : numsVec) {
        auto res = s.permute(nums);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &v : res) {
            std::cout << "    [";
            for (const auto &n : v)
                std::cout << n << ", ";
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    }
}