/**
 * According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular
 * automaton devised by the British mathematician John Horton Conway in 1970."
 *
 * Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell
 * interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four
 * rules (taken from the above Wikipedia article):
 *
 * Any live cell with fewer than two live neighbors dies, as if caused by under-population.
 * Any live cell with two or three live neighbors lives on to the next generation.
 * Any live cell with more than three live neighbors dies, as if by over-population..
 * Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 * Write a function to compute the next state (after one update) of the board given its current
 * state. The next state is created by applying the above rules simultaneously to every cell in the
 * current state, where births and deaths occur simultaneously.
 *
 * Example:
 * Input:
 * [
 *   [0,1,0],
 *   [0,0,1],
 *   [1,1,1],
 *   [0,0,0]
 * ]
 * Output:
 * [
 *   [0,0,0],
 *   [1,0,1],
 *   [0,1,1],
 *   [0,1,0]
 * ]
 *
 * Follow up:
 * Could you solve it in-place? Remember that the board needs to be updated at the same time: You
 * cannot update some cells first and then use their updated values to update other cells. In this
 * question, we represent the board using a 2D array. In principle, the board is infinite, which
 * would cause problems when the active area encroaches the border of the array. How would you
 * address these problems?
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    void gameOfLife(std::vector<std::vector<int>> &board) {
        BOTTOM = board.size() - 1, RIGHT = board[0].size() - 1;
        LEFT = TOP = 0;
        for (auto r = 0; r <= BOTTOM; ++r) {
            for (auto c = 0; c <= RIGHT; ++c) {
                auto alives = aliveNeighbors(board, r, c);
                // std::cout << "alives = " << alives << std::endl;
                if ((alives < 2 || alives > 3) && board[r][c] != 0) {
                    board[r][c] = kFlagLiveToDie;
                } else if (alives == 3 && board[r][c] != 1) {
                    board[r][c] = kFlagDieToLive;
                }
            }
        }

        for (auto r = 0; r <= BOTTOM; ++r) {
            for (auto c = 0; c <= RIGHT; ++c) {
                if (board[r][c] == kFlagLiveToDie) {
                    board[r][c] = 0;
                } else if (board[r][c] == kFlagDieToLive) {
                    board[r][c] = 1;
                }
            }
        }
    }

private:
    int aliveNeighbors(const std::vector<std::vector<int>> &board, int row, int col) {
        auto left = (col - 1) < LEFT ? LEFT : (col - 1);
        auto right = (col + 1) > RIGHT ? RIGHT : (col + 1);
        auto top = (row - 1) < TOP ? TOP : (row - 1);
        auto bottom = (row + 1) > BOTTOM ? BOTTOM : (row + 1);
        int alives = 0;
        // std::cout << "check border [" << top << ", " << left << "; " << bottom << ", " << right
        //           << "] for (" << row << ", " << col << ")\n";
        for (auto r = top; r <= bottom; ++r) {
            for (auto c = left; c <= right; ++c) {
                if (r == row && c == col) continue;
                // std::cout << r << ", " << c << std::endl;
                if (board[r][c] == 1 || board[r][c] == kFlagLiveToDie) ++alives;
            }
        }
        return alives;
    }

    int LEFT, RIGHT, TOP, BOTTOM;
    int kFlagLiveToDie = 2;
    int kFlagDieToLive = 3;
};

int main() {
    Solution sln;

    std::vector<std::vector<std::vector<int>>> boards{{{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}}};

    auto disp_board = [](const std::vector<std::vector<int>> &board) {
        std::cout << "[\n";
        for (const std::vector<int> &line : board) {
            std::cout << "\t[";
            for (const auto &cell : line) { std::cout << cell << ", "; }
            std::cout << "],\n";
        }
        std::cout << "]\n";
    };

    for (auto &board : boards) {
        TestCount();
        sln.gameOfLife(board);
        disp_board(board);
    }
}