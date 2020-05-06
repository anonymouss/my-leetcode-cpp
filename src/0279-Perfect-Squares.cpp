/**
 * Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4,
 * 9, 16, ...) which sum to n.
 *
 * Example 1:
 * Input: n = 12
 * Output: 3 
 * Explanation: 12 = 4 + 4 + 4.
 *
 * Example 2:
 * Input: n = 13
 * Output: 2
 * Explanation: 13 = 4 + 9.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int numSquares(int n) {
        int *dp = new int[n + 1];
        dp[0] = 0;
        for (auto i = 1; i <= n; ++i) {
            dp[i] = i;
            for (auto j = 1; j * j <= i; ++j) {
                dp[i] = std::min(dp[i], dp[i - j * j] + 1);
            }
        }
        auto res = dp[n];
        delete [] dp;
        return res;
    }
};

int main() {
    Solution sln;

    std::vector<int> ns{12, 13};

    for (auto &n : ns) {
        TestCount();
        std::cout << sln.numSquares(n) << std::endl;
    }
}