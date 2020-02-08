/**
 * Say you have an array for which the i-th element is the price of a given stock on day i.
 * Design an algorithm to find the maximum profit. You may complete at most k transactions.
 *
 * Note:
 * You may not engage in multiple transactions at the same time (ie, you must sell the stock before
 * you buy again).
 *
 * Example 1:
 * Input: [2,4,1], k = 2
 * Output: 2
 * Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
 * 
 * Example 2:
 * Input: [3,2,6,5,0,3], k = 2
 * Output: 7
 * Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
 *              Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 */

#include "MyMisc.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>

class Solution {
public:
    int maxProfit(int k, std::vector<int> &prices) {
        auto N = prices.size();
        if (k > N / 2) {
            // k could be ignored
            int dp_i_0 = 0, dp_i_1 = INT_MIN;
            for (auto i = 0; i < N; ++i) {
                auto tmp = dp_i_0;
                //                hold    sell
                dp_i_0 = std::max(dp_i_0, dp_i_1 + prices[i]);
                //                hold    buy
                dp_i_1 = std::max(dp_i_1, tmp - prices[i]);
            }
            return dp_i_0;
        } else {
            std::vector<std::vector<std::vector<int>>> dp(N, std::vector<std::vector<int>>(k + 1,
                    std::vector<int>(2)));
            for (auto i = 0; i < N; ++i) {
                for (auto j = k; j >= 1; --j) {
                    if (i - 1 == -1) {
                        dp[i][j][0] = 0;
                        dp[i][j][1] = -prices[i];
                        continue;
                    }
                    dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                    dp[i][j][1] = std::max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
                }
            }
            return dp[N - 1][k][0];
        }
    }
};

int main() {
    Solution sln;

    std::vector<int> kv{2, 2};
    std::vector<std::vector<int>> pv{
        {2, 4, 1},
        {3, 2, 6, 5, 0, 3}
    };

    for (auto i = 0; i < kv.size(); ++i) {
        TestCount();
        std::cout << sln.maxProfit(kv[i], pv[i]) << std::endl;
    }
}