/**
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two
 * queens attack each other.
 * [one solution to the eight queens puzzle](https://assets.leetcode.com/uploads/2018/10/12/8-queens.png)
 *
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 * Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and
 * '.' both indicate a queen and an empty space respectively.
 *
 * Example:
 * Input: 4
 * Output: [
 *  [".Q..",  // Solution 1
 *   "...Q",
 *   "Q...",
 *   "..Q."],
 *
 *  ["..Q.",  // Solution 2
 *   "Q...",
 *   "...Q",
 *   ".Q.."]
 * ]
 * Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
 */

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> sol(n, string(n, '.'));
        vector<int> pos(n, -1);
        queue(0, n, pos, sol, res);
        return res;
    }

    // backtracking...
    void queue(int row, int n, vector<int> &pos, vector<string> &sol, vector<vector<string>> &res) {
        if (row == n) {
            res.emplace_back(sol);
        } else {
            for (int col = 0; col < n; ++col) {
                pos[row] = col;
                if (isSafe(row, pos)) {
                    sol[row][col] = 'Q';
                    queue(row + 1, n, pos, sol, res);
                }
                sol[row][col] = '.';
            }
        }
    }

    bool isSafe(int row, vector<int> &pos) {
        for (int c = 0; c < row; ++c) {
            if (pos[c] == pos[row]                          /* vertical | */
                    || (c - pos[c]) == (row - pos[row])     /* diagonal \ */
                    || (c + pos[c]) == (row + pos[row])) {  /* diagonal / */
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<int> ns{4, 8};

    for (auto &n : ns) {
        auto res = s.solveNQueens(n);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &sl : res) {
            std::cout << "    [\n";
            for (const auto &s : sl) {
                std::cout << "      \"" << s << "\"," << std::endl;
            }
            std::cout << "    ],\n";
        }
        std::cout << "  ]" << std::endl;
    }
}