/**
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 * The robot can only move either down or right at any point in time. The robot is trying to reach
 * the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 * How many possible unique paths are there?
 *
 * [7x3_grid](https://assets.leetcode.com/uploads/2018/10/22/robot_maze.png)
 * Above is a 7 x 3 grid. How many possible unique paths are there?
 *
 * Note: m and n will be at most 100.
 *
 * Example 1:
 * Input: m = 3, n = 2
 * Output: 3
 * Explanation:
 * From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
 * 1. Right -> Right -> Down
 * 2. Right -> Down -> Right
 * 3. Down -> Right -> Right
 *
 * Example 2:
 * Input: m = 7, n = 3
 * Output: 28
 */

#include "../utils/MyClock.h"

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERSION 2

#if (COMPILE_VERSION == 0)
// back tracking --- TLE
class Solution {
public:
    int paths = 0;

    int uniquePaths(int m, int n) {
#ifdef DEBUG
        MyClock<MY_MS> myClock;
#endif
        paths = 0;
        backtracking(0, 0, m - 1, n - 1);
        return paths;
    }

    void backtracking(int posm, int posn, int endm, int endn) {
        if (posm == endm && posn == endn) {
            ++paths;
        } else if (posm == endm) {
            backtracking(posm, posn + 1, endm, endn);
        } else if (posn == endn) {
            backtracking(posm + 1, posn, endm, endn);
        } else {
            backtracking(posm + 1, posn, endm, endn);
            backtracking(posm, posn + 1, endm, endn);
        }
    }
};
#elif (COMPILE_VERSION == 1)
// dp
class Solution {
public:
    int uniquePaths(int m, int n) {
#ifdef DEBUG
        MyClock<MY_MS> myClock;
#endif
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int im = 1; im < m; ++im) {
            for (int in = 1; in < n; ++in) {
                dp[im][in] = dp[im-1][in] + dp[im][in-1];
            }
        }
        return dp[m-1][n-1];
    }
};
#elif (COMPILE_VERSION == 2)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
// formula .. C_(n-1 + m-1)^(m-1) = (m+n-2)! / ((m-1)! * (n-1)!)
class Solution {
public:
    int uniquePaths(int m, int n) {
#ifdef DEBUG
        MyClock<MY_MS> myClock;
#endif
        auto min = MIN(m, n) - 1;
        auto max = MAX(m, n) - 1;
        uint64_t num = 1, deno = 1;
        for (int i = 1; i <= min; ++i) {
            num *= (max + i);
            deno *= i;
        }
        return static_cast<int>(num / deno);
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> mns{
        // m, n
        {3, 2},
        {7, 3},
        {23, 12}
    };

    for(const auto &mn : mns) {
        auto paths = s.uniquePaths(mn[0], mn[1]);
        std::cout << "Case " << testId++ << ": " << paths << std::endl;
    }
}