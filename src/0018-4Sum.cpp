/**
 * Given an array nums of n integers and an integer target, are there elements
 * a, b, c, and d in nums such that a + b + c + d = target? Find all unique
 * quadruplets in the
 * array which gives the sum of target.
 *
 * Note: The solution set must not contain duplicate quadruplets.
 *
 * Example:
 * Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.
 * A solution set is:
 * [
 *   [-1,  0, 0, 1],
 *   [-2, -1, 1, 2],
 *   [-2,  0, 0, 2]
 * ]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int size = nums.size();
        for (int i = 0; i < size - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < size - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                int l = j + 1, r = size - 1;
                int a = nums[i], b = nums[j];
                auto skipLeft =
                    [&]() { while (l < size && nums[l] == nums[l + 1]) ++l; };
                auto skipRight =
                    [&]() { while (r > i && nums[r] == nums[r - 1]) --r; };
                while (l < r) {
                    int c = nums[l], d = nums[r];
                    auto sum = a + b + c + d;
                    if (sum == target) {
                        res.emplace_back(vector<int>({a, b, c, d}));
                        skipLeft(); skipRight();
                        ++l, --r;
                    } else if (sum < target) {
                        skipLeft();
                        ++l;
                    } else {
                        skipRight();
                        --r;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;

    vector<int> nums1{1, 0, -1, 0, -2, 2}; int target1 = 0;

    auto exeTest = [&](vector<int> &vec, int target, int testId) {
        auto res = s.fourSum(vec, target);
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

    exeTest(nums1, target1, 1);
}