/**
 * Given a list of non negative integers, arrange them such that they form the largest number.
 * Example 1:
 * Input: [10,2]
 * Output: "210"
 *
 * Example 2:
 * Input: [3,30,34,5,9]
 * Output: "9534330"
 * Note: The result may be very large, so you need to return a string instead of an integer.
 */

#include "MyMisc.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Solution {
public:
    std::string largestNumber(std::vector<int> &nums) {
        if (std::all_of(nums.begin(), nums.end(), [](int v) { return v == 0; })) { return "0"; }
        std::vector<std::string> numsStr(nums.size());
        std::transform(nums.begin(), nums.end(), numsStr.begin(),
                       [](int v) { return std::to_string(v); });
        std::sort(numsStr.begin(), numsStr.end(),
                  [](const std::string &s1, const std::string &s2) { return s1 + s2 > s2 + s1; });
        return std::accumulate(numsStr.begin(), numsStr.end(), std::string());
    }
};

int main() {
    Solution sln;
    std::vector<std::vector<int>> numsVec{{10, 2}, {3, 30, 34, 5, 9}};

    for (auto &nums : numsVec) {
        TestCount();
        std::cout << sln.largestNumber(nums) << std::endl;
    }
}