/**
 * Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
 * A region is captured by flipping all 'O's into 'X's in that surrounded region.
 *
 * Example:
 * X X X X
 * X O O X
 * X X O X
 * X O X X
 * After running your function, the board should be:
 * X X X X
 * X X X X
 * X X X X
 * X O X X
 * Explanation:
 * Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board
 * are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on the
 * border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected
 * horizontally or vertically.
 */

#include "../utils/MyMisc.h"
#include "../utils/MyContainerUtil.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::min;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i) {
            dfs(board, i, 0, m, n);
            if (n > 1) dfs(board, i, n - 1, m, n);
        }
        for (int j = 1; j < n - 1; ++j) {
            dfs(board, 0, j, m, n);
            if (m > 1) dfs(board, m - 1, j, m, n);
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                else if (board[i][j] == '-') board[i][j] = 'O';
            }
        }
    }

    void dfs(vector<vector<char>> &board, int i, int j, int m, int n) {
        if (board[i][j] == 'O') {
            board[i][j] = '-';
            if (i > 1) dfs(board, i - 1, j, m, n);
            if (j > 1) dfs(board, i, j - 1, m, n);
            if (i + 1 < m) dfs(board, i + 1, j, m, n);
            if (j + 1 < n) dfs(board, i, j + 1, m, n);
        }
    }
};

int main() {
    Solution s;

    using Board = vector<vector<char>>;
    vector<Board> boards{
        {
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'X'}
        },
        {
            {'O', 'X', 'X', 'O', 'X'},
            {'X', 'O', 'O', 'X', 'O'},
            {'X', 'O', 'X', 'O', 'X'},
            {'O', 'X', 'O', 'O', 'O'},
            {'X', 'X', 'O', 'X', 'O'}
        }
    };

    for (auto &board : boards) {
        TestCount();
        s.solve(board);
        myDispVector2D(board);
    }
}