/**
 * Say you have an array for which the ith element is the price of a given stock on day i.
 * Design an algorithm to find the maximum profit. You may complete at most two transactions.
 * Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock
 * before you buy again).
 *
 * Example 1:
 * Input: [3,3,5,0,0,3,1,4]
 * Output: 6
 * Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 *              Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
 *
 * Example 2:
 * Input: [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
 *              Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
 *              engaging multiple transactions at the same time. You must sell before buying again.
 *
 * Example 3:
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;
using std::min;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
// https://www.cnblogs.com/TenosDoIt/p/3436457.html
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int length = prices.size();
        if (length <= 1) return 0;
        vector<int> maxProfits(length, 0);
        int minPrice = prices[0], maxProfit = 0;
        for (int i = 1; i < length; ++i) {
            minPrice = min(minPrice, prices[i-1]);
            auto diff = prices[i] - minPrice;
            if (maxProfit < diff) maxProfit = diff;
            maxProfits[i] = maxProfit;
        }
        maxProfit = maxProfits[length-1];
        int rightMax = 0;
        int maxPrice = prices[length-1];
        for (int i = length - 2; i >= 0; --i) {
            maxPrice = max(maxPrice, prices[i]);
            auto diff = maxPrice - prices[i];
            if (diff > rightMax) rightMax = diff;
            auto sum = rightMax + maxProfits[i];
            if (sum > maxProfit) maxProfit = sum;
        }
        return maxProfit;
    }
};
#elif (COMPILE_VERSION == 1)
// https://www.cnblogs.com/grandyang/p/4281975.html
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int length = prices.size();
        if (length <= 1) return 0;
        vector<vector<int>> globalMax(length, vector<int>(3, 0));
        vector<vector<int>> localMax(length, vector<int>(3, 0));
        for (int i = 1; i < length; ++i) {
            auto diff = prices[i] - prices[i-1];
            for (int j = 1; j <= 2; ++j) {
                localMax[i][j] = max(globalMax[i-1][j-1] + max(diff, 0), localMax[i-1][j] + diff);
                globalMax[i][j] = max(localMax[i][j], globalMax[i-1][j]);
            }
        }
        return globalMax[length-1][2];
    }
};
#endif

int main() {
    Solution s;

    vector<vector<int>> pricesVec{
        {3, 3, 5, 0, 0, 3, 1, 4},
        {1, 2, 3, 4, 5},
        {7, 6, 4, 3, 1}
    };

    for (auto &prices : pricesVec) {
        TestCount();
        auto profit = s.maxProfit(prices);
        std::cout << profit << std::endl;
    }
}