/**
 * Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's
 * and return its area.
 *
 * Example:
 * Input: 
 * 1 0 1 0 0
 * 1 0 1 1 1
 * 1 1 1 1 1
 * 1 0 0 1 0
 * Output: 4
 */

#include "MyMisc.h"

#include <vector>
#include <iostream>
#include <algorithm>

class Solution {
public:
    int maximalSquare(std::vector<std::vector<char>> &matrix) {
        auto rows = matrix.size();
        if (rows == 0) return 0;
        auto cols = matrix[0].size();

        std::vector<int> dp(cols + 1, 0);
        int maxWidth = 0, prev = 0;
        for (auto r = 1; r <= rows; ++r) {
            for (auto c = 1; c <= cols; ++c) {
                auto t = dp[c]; // save before update
                if (matrix[r - 1][c - 1] == '1') {
                    dp[c] = std::min(std::min(dp[c - 1], prev), dp[c]) + 1;
                    maxWidth = std::max(maxWidth, dp[c]);
                } else {
                    dp[c] = 0;
                }
                prev = t;
            }
        }
        return maxWidth * maxWidth;
    }
};

int main() {
    Solution sln;

    using T = std::vector<std::vector<char>>;

    std::vector<T> matrixes{
        {
            {'1', '0', '1', '0', '0'},
            {'1', '0', '1', '1', '1'},
            {'1', '1', '1', '1', '1'},
            {'1', '0', '0', '1', '0'}
        }
    };

    for (auto &matrix : matrixes) {
        TestCount();
        std::cout << sln.maximalSquare(matrix) << std::endl;
    }
}