/**
 * Given an array nums of n integers, are there elements a, b, c in nums such
 * that a + b + c = 0? Find all unique triplets in the array which gives the sum
 * of zero.
 *
 * Note: The solution set must not contain duplicate triplets.
 *
 * Example:
 * Given array nums = [-1, 0, 1, 2, -1, -4],
 * A solution set is:
 * [
 *   [-1, 0, 1],
 *   [-1, -1, 2]
 * ]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int size = nums.size();
        vector<vector<int>> res;
        for (int i = 0; i < size - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int target = nums[i], l = i + 1, r = size - 1; 
            auto skipLeft =
                [&]() { while (l < size && nums[l] == nums[l + 1]) ++l; };
            auto skipRight =
                [&]() { while (r > i && nums[r] == nums[r - 1]) --r; };
            while (l < r) {
                int a = nums[l], b = nums[r];
                if (a + b + target == 0) {
                    res.emplace_back(vector<int>{target, a, b});
                    skipLeft(), skipRight();
                    ++l, --r;
                } else if (a + b + target > 0) {
                    skipRight();
                    --r;
                } else { // < 0
                    skipLeft();
                    ++l;
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;

    vector<int> vec1{-1, 0, 1, 2, -1, -4};
    vector<int> vec2{-4, -2, 1, -5, -4, -4, 4, -2, 0, 4, 0, -2, 3, 1, -5, 0};

    auto exeTest = [&](vector<int> &vec, int testId) {
        auto res = s.threeSum(vec);
        std::cout << "Case " << testId << ":" << std::endl;
        std::cout << "  [\n";
        for (const auto &vec : res) {
            std::cout << "    [";
            for (const auto &e : vec) {
                std::cout << e << ", ";
            }
            std::cout << "],\n";
        }
        std::cout << "  ]\n";
    };

    exeTest(vec1, 1);
    exeTest(vec2, 2);
}