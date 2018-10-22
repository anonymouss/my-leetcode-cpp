/**
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two
 * queens attack each other.
 * [one solution to the eight queens puzzle](https://assets.leetcode.com/uploads/2018/10/12/8-queens.png)
 *
 * Given an integer n, return the number of distinct solutions to the n-queens puzzle.
 *
 * Example:
 * Input: 4
 * Output: 2
 * Explanation: There are two distinct solutions to the 4-queens puzzle as shown below.
 * [
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
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    int total = 0;

    int totalNQueens(int n) {
        vector<int> pos(n, -1);
        queue(0, n, pos);
        return total;
    }

    void queue(int row, int n, vector<int> &pos) {
        if (row == n) {
            ++total;
        } else {
            for (int c = 0; c < n; ++c) {
                pos[row] = c;
                if (isSafe(row, pos)) {
                    queue(row + 1, n, pos);
                }
            }
        }
    }

    bool isSafe(int row, vector<int> &pos) {
        for (int c = 0; c < row; ++c) {
            if (pos[c] == pos[row] || c - pos[c] == row - pos[row]
                    || c + pos[c] == row + pos[row])
                return false;
        }
        return true;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<int> ns{4, 8};

    for (auto &n : ns) {
        auto res = s.totalNQueens(n);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}