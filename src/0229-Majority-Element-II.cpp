/**
 * Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
 * Note: The algorithm should run in linear time and in O(1) space.
 *
 * Example 1:
 * Input: [3,2,3]
 * Output: [3]
 *
 * Example 2:
 * Input: [1,1,1,3,3,2,2,2]
 * Output: [1,2]
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

// pass, but not O(1) space
#if 0
class Solution {
public:
    std::vector<int> majorityElement(std::vector<int> &nums) {
        std::vector<int> majs;
        std::unordered_map<int, int> counter;
        for (auto &n : nums) {
            counter[n]++;
        }
        auto times = std::floor(static_cast<float>(nums.size()) / 3.0);
        for (auto &p : counter) {
            if (p.second > times) {
                majs.emplace_back(p.first);
            }
        }
        return majs;
    }
};
#endif
class Solution {
public:
    std::vector<int> majorityElement(std::vector<int> &nums) {
        if (nums.empty()) return {};
        int e1= nums[0], e2 = nums[0];
        int c1 = 0, c2 = 0;
        for (auto &n : nums) {
            if ((n == e1 || c1 == 0) && n != e2) {
                e1 = n;
                ++c1;
            } else if (n == e2 || c2 == 0) {
                e2 = n;
                ++c2;
            } else {
                --c1;
                --c2;
            }
        }
        std::vector<int> majs;
        c1 = 0;
        c2 = 0;
        for (auto &n : nums) {
            if (n == e1) ++c1;
            else if (n == e2) ++c2;
        }
        auto times = nums.size() / 3;
        if (c1 > times) majs.emplace_back(e1);
        if (c2 > times) majs.emplace_back(e2);
        return majs;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> numsv{
        {3, 2, 3},
        {1, 1, 1, 3, 3, 2, 2, 2}
    };

    auto print_v = [](const std::vector<int> elements) {
        std::cout << "[";
        for (auto &e : elements) {
            std::cout << e << ", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &nums : numsv) {
        TestCount();
        print_v(sln.majorityElement(nums));
    }
}