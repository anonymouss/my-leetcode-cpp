/**
 * You are climbing a stair case. It takes n steps to reach to the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * Note: Given n will be a positive integer.
 *
 * Example 1:
 * Input: 2
 * Output: 2
 * Explanation: There are two ways to climb to the top.
 * 1. 1 step + 1 step
 * 2. 2 steps
 * Example 2:
 *
 * Input: 3
 * Output: 3
 * Explanation: There are three ways to climb to the top.
 * 1. 1 step + 1 step + 1 step
 * 2. 1 step + 2 steps
 * 3. 2 steps + 1 step
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int climbStairs(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        vector<int> dp(n+1, 1);
        for (int i = 2; i <= n; ++i)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<int> ns{0, 1, 2, 3, 4, 5, 6};

    for (auto &n : ns) {
        auto res = s.climbStairs(n);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}