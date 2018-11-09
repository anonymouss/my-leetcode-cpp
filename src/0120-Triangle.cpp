/**
 * Given a triangle, find the minimum path sum from top to bottom. Each step you may move to
 * adjacent numbers on the row below.
 *
 * For example, given the following triangle
 * [
 *      [2],
 *     [3,4],
 *    [6,5,7],
 *   [4,1,8,3]
 * ]
 * The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
 *
 * Note: Bonus point if you are able to do this using only O(n) extra space, where n is the total
 * number of rows in the triangle.
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::min;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        vector<int> dp(triangle.back().size(), 0);
        dp[0] = triangle[0][0];
        for (int i = 1; i < triangle.size(); ++i) {
            int prev = INT32_MAX;
            for (int j = 0; j <= i; ++j) {
                int cur = (i == j) ? INT32_MAX : dp[j];
                dp[j] = min(prev, cur) + triangle[i][j];
                prev = cur;
            }
        }
        int minTotal = INT32_MAX;
        for (auto &v : dp) minTotal = v < minTotal ? v : minTotal;
        return minTotal;
    }
};

int main() {
    Solution s;

    vector<vector<vector<int>>> triangles{
        {},
        {
            {2},
            {3, 4},
            {6, 5, 7},
            {4, 1, 8, 3}
        }
    };

    for (auto &triangle : triangles) {
        TestCount();
        auto total = s.minimumTotal(triangle);
        std::cout << total << std::endl;
    }
}