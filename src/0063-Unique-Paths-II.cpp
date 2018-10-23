/**
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 * The robot can only move either down or right at any point in time. The robot is trying to reach
 * the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 * 
 * Now consider if some obstacles are added to the grids. How many unique paths would there be?
 *
 * [7x3_grid](https://assets.leetcode.com/uploads/2018/10/22/robot_maze.png)
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 *
 * Note: m and n will be at most 100.
 *
 * Example 1:
 * Input:
 * [
 *   [0,0,0],
 *   [0,1,0],
 *   [0,0,0]
 * ]
 * Output: 2
 *
 * Explanation:
 * There is one obstacle in the middle of the 3x3 grid above.
 * There are two ways to reach the bottom-right corner:
 * 1. Right -> Right -> Down -> Down
 * 2. Down -> Down -> Right -> Right
 */

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
// backtracking ... TLE
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid.empty()) return 0;
        return backtracking(obstacleGrid, 0, 0, obstacleGrid.size() - 1,
            obstacleGrid[0].size() - 1);
    }

    int backtracking(vector<vector<int>> &abstacleGrid, int posm, int posn, int endm, int endn) {
        if (posm > endm || posn > endn) return 0;
        if (abstacleGrid[posm][posn] == 1) return 0;
        if (posm == endm && posn == endn) return 1;
        return backtracking(abstacleGrid, posm + 1, posn, endm, endn) +
            backtracking(abstacleGrid, posm, posn + 1, endm, endn);
    }
};
#elif (COMPILE_VERSION == 1)
// dp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        if (obstacleGrid.empty()) return 0;
        if (obstacleGrid[0][0] == 1) return 0;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;
        for (int i = 1; i < n; ++i) {
            if (obstacleGrid[0][i] == 1) break;
            dp[0][i] = 1;
        }
        for (int i = 1; i < m; ++i) {
            if (obstacleGrid[i][0] == 1) break;
            dp[i][0] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] == 0)
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<vector<vector<int>>> obstacleGrids{
        {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        },
        {
            {1}
        }
    };

    for (auto &obstacleGrid : obstacleGrids) {
        auto paths = s.uniquePathsWithObstacles(obstacleGrid);
        std::cout << "Case " << testId++ << ": " << paths << std::endl;
    }
}