/**
 * Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 * Your algorithm should run in O(n) complexity.
 *
 * Example:
 * Input: [100, 4, 200, 1, 3, 2]
 * Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <vector>
#include <unordered_set> // hash set
#include <algorithm>

using std::vector;
using std::unordered_set;
using std::max;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> table(nums.begin(), nums.end());
        int length = 0;
        for (auto &n : nums) {
            if (!table.count(n)) continue;
            table.erase(n);
            int pre = n - 1, next = n + 1;
            while (table.count(pre)) table.erase(pre--);
            while (table.count(next)) table.erase(next++);
            length = max(length, next - pre - 1);
        }
        return length;
    }
};

int main() {
    Solution s;

    vector<vector<int>> numsInput{
        {100, 4, 200, 1, 3, 2}
    };

    for (auto &nums : numsInput) {
        TestCount();
        auto res = s.longestConsecutive(nums);
        std::cout << res << std::endl;
    }
}