/**
 * Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be
 * validated according to the following rules:
 * - Each row must contain the digits `1-9` without repetition.
 * - Each column must contain the digits `1-9` without repetition.
 * - Each of the 9 `3x3` sub-boxes of the grid must contain the digits 1-9
 *   without repetition.
 *
 * A partially filled sudoku which is valid.
 * The Sudoku board could be partially filled, where empty cells are filled with
 * the character '.'.
 *
 * Example 1:
 * Input:
 * [
 *   ["5","3",".",".","7",".",".",".","."],
 *   ["6",".",".","1","9","5",".",".","."],
 *   [".","9","8",".",".",".",".","6","."],
 *   ["8",".",".",".","6",".",".",".","3"],
 *   ["4",".",".","8",".","3",".",".","1"],
 *   ["7",".",".",".","2",".",".",".","6"],
 *   [".","6",".",".",".",".","2","8","."],
 *   [".",".",".","4","1","9",".",".","5"],
 *   [".",".",".",".","8",".",".","7","9"]
 * ]
 * Output: true
 *
 * Example 2:
 * Input:
 * [
 *   ["8","3",".",".","7",".",".",".","."],
 *   ["6",".",".","1","9","5",".",".","."],
 *   [".","9","8",".",".",".",".","6","."],
 *   ["8",".",".",".","6",".",".",".","3"],
 *   ["4",".",".","8",".","3",".",".","1"],
 *   ["7",".",".",".","2",".",".",".","6"],
 *   [".","6",".",".",".",".","2","8","."],
 *   [".",".",".","4","1","9",".",".","5"],
 *   [".",".",".",".","8",".",".","7","9"]
 * ]
 * Output: false
 * Explanation: Same as Example 1, except with the 5 in the top left corner
 * being modified to 8. Since there are two 8's in the top left 3x3 sub-box,
 * it is invalid.
 *
 * Note:
 * A Sudoku board (partially filled) could be valid but is not necessarily
 * solvable.
 * Only the filled cells need to be validated according to the mentioned rules.
 * The given board contain only digits `1-9` and the character '.'.
 * The given board size is always `9x9`.
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    // brute force
    bool isValidSudoku(vector<vector<char>>& board) {
        // validate rows
        for (const auto &row : board) {
            if (validGroup(std::move(row)) == false)
                return false;
        }

        // validate cols
        for (int i = 0; i < 9; ++i) {
            if (validGroup({board[0][i], board[1][i], board[2][i],
                            board[3][i], board[4][i], board[5][i],
                            board[6][i], board[7][i], board[8][i]}) == false)
                return false;
        }

        // validate blocks
        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 9; j +=3) {
                if (validGroup({
                        board[j][i],     board[j][i + 1],     board[j][i + 2],
                        board[j + 1][i], board[j + 1][i + 1], board[j + 1][i + 2],
                        board[j + 2][i], board[j + 2][i + 1], board[j + 2][i + 2]
                        }) == false)
                    return false;
            }
        }

        return true;
    }

    bool validGroup(const vector<char>&& group) {
        vector<int> hash(10, 0);
        for (const auto &g : group) {
            if (g == '.') continue;
            if (hash[g - '0'] == 0) hash[g - '0']++;
            else return false;
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

    vector<vector<char>> board2{{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    auto exeTest = [&](vector<vector<char>> &board) {
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": ";
        std::cout << s.isValidSudoku(board) << std::endl;
    };

    exeTest(board1);
    exeTest(board2);
}