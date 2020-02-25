/**
 * Given a sorted integer array without duplicates, return the summary of its ranges.
 *
 * Example 1:
 * Input:  [0,1,2,4,5,7]
 * Output: ["0->2","4->5","7"]
 * Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.
 *
 * Example 2:
 * Input:  [0,2,3,4,6,8,9]
 * Output: ["0","2->4","6","8->9"]
 * Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> summaryRanges(std::vector<int> &nums) {
        std::vector<std::string> ranges;
        if (nums.size() == 0) {
            return ranges;
        }

        nums.emplace_back(nums[nums.size() - 1]); // extend
        std::string range{""};
        int head, prev;
        for (auto i = 0; i < nums.size(); ++i) {
            if (range == "") {
                range += std::to_string(nums[i]);
                prev = nums[i];
                head = nums[i];
            } else {
                if (nums[i] - 1 == prev) {
                    prev = nums[i];
                } else {
                    if (head != prev) {
                        range += "->";
                        range += std::to_string(prev);
                    }
                    ranges.emplace_back(range);
                    range = "";
                    --i;
                }
            }
        }
        return ranges;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> numsv{
        {0, 1, 2, 4, 5, 7},
        {0, 2, 3, 4, 6, 8, 9},
        {-2147483648, -2147483647, 2147483647},
        {0, 1, 2, 4, 5, 7}
    };

    auto print_s = [](const std::vector<std::string> &ranges) {
        std::cout << "[";
        for (const auto &range : ranges) {
            std::cout << "\"" << range << "\", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &nums : numsv) {
        TestCount();
        print_s(sln.summaryRanges(nums));
    }
}