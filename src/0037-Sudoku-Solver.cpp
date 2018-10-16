/**
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * A sudoku solution must satisfy all of the following rules:
 * - Each of the digits `1-9` must occur exactly once in each row.
 * - Each of the digits `1-9` must occur exactly once in each column.
 * - Each of the the digits `1-9` must occur exactly once in each of the 9 `3x3`
 *   sub-boxes of the grid.
 * Empty cells are indicated by the character '.'.
 *
 *   '5', '3', '.', '.', '7', '.', '.', '.', '.'
 *   '6', '.', '.', '1', '9', '5', '.', '.', '.'
 *   '.', '9', '8', '.', '.', '.', '.', '6', '.'
 *   '8', '.', '.', '.', '6', '.', '.', '.', '3'
 *   '4', '.', '.', '8', '.', '3', '.', '.', '1'
 *   '7', '.', '.', '.', '2', '.', '.', '.', '6'
 *   '.', '6', '.', '.', '.', '.', '2', '8', '.'
 *   '.', '.', '.', '4', '1', '9', '.', '.', '5'
 *   '.', '.', '.', '.', '8', '.', '.', '7', '9'
 * A sudoku puzzle...
 *
 *   '5', '3', [4], [6], '7', [8], [9], [1], [2]
 *   '6', [7], [2], '1', '9', '5', [3], [4], [8]
 *   [1], '9', '8', [3], [4], [2], [5], '6', [7]
 *   '8', [5], [9], [7], '6', [1], [4], [2], '3'
 *   '4', [2], [6], '8', [5], '3', [7], [9], '1'
 *   '7', [1], [3], [9], '2', [4], [8], [5], '6'
 *   [9], '6', [1], [5], [3], [7], '2', '8', [4]
 *   [2], [8], [7], '4', '1', '9', [6], [3], '5'
 *   [3], [4], [5], [2], '8', [6], [1], '7', '9'
 * ...and its solution numbers marked in red.
 *
 * Note:
 * The given board contain only digits 1-9 and the character '.'.
 * You may assume that the given Sudoku puzzle will have a single unique
 * solution.
 * The given board size is always 9x9.
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solveSudokuDFS(board, 0, 0);
    }

    bool solveSudokuDFS(vector<vector<char>> &board, int row, int col) {
        if (row == 9) return true;
        if (col == 9) return solveSudokuDFS(board, row + 1, 0);
        if (board[row][col] == '.') {
            for (int i = 1; i <=9; ++i) {
                board[row][col] = '0' + i;
                if (isValid(board, row, col)) {
                    if (solveSudokuDFS(board, row, col + 1)) return true;
                }
                board[row][col] = '.';
            }
        } else {
            return solveSudokuDFS(board, row, col + 1);
        }
        return false;
    }

    bool isValid(vector<vector<char>> &board, int row, int col) {
        for (int c = 0; c < 9; ++c) {
            if (c != col && board[row][col] == board[row][c]) return false;
        }
        for (int r = 0; r < 9; ++r) {
            if (r != row && board[row][col] == board[r][col]) return false;
        }
        for (int r = row / 3 * 3; r < row / 3 * 3 + 3; ++r) {
            for (int c = col / 3 * 3; c < col / 3 * 3 + 3; ++c) {
                if ((r != row || c != col) && board[row][col] == board[r][c])
                    return false;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    int testId = 1;
    vector<vector<char>> board1{{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    auto exeTest = [&](vector<vector<char>> &board) {
        std::cout << "Case " << testId++ << ":\n  [\n";
        s.solveSudoku(board);
        for (int row = 0; row < 9; ++row) {
            std::cout << "    [";
            for (int col = 0; col < 9; ++col) {
                std::cout << "'" << board[row][col] << "', ";
            }
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    };

    exeTest(board1);
}