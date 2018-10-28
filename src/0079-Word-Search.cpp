/**
 * Given a 2D board and a word, find if the word exists in the grid.
 * The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells
 * are those horizontally or vertically neighboring. The same letter cell may not be used more than
 * once.
 *
 * Example:
 * board =
 * [
 *   ['A','B','C','E'],
 *   ['S','F','C','S'],
 *   ['A','D','E','E']
 * ]
 * Given word = "ABCCED", return true.
 * Given word = "SEE", return true.
 * Given word = "ABCB", return false.
 */

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using std::vector;
using std::pair;
using std::string;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        for (int x = 0; x < board.size(); ++x) {
            for (int y = 0; y < board[0].size(); ++y) {
                // std::cout << "Starts from [" << x << ", " << y << "]\n";
                if (dfs(board, word, x, y, 0)) return true;
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>> &borad, string &word, int x, int y, int i) {
        if (i == word.length()) return true;
        if (x < 0 || x >= borad.size() || y < 0 || y >= borad[0].size() || borad[x][y] != word[i])
            return false;
        // std::cout << "[" << x << ", " << y << "] : " << borad[x][y]
        //         << " -- i " << i << " : " << word[i] << std::endl;
        borad[x][y] += 128;
        bool exist = dfs(borad, word, x+1, y, i+1) || dfs(borad, word, x, y+1, i+1)
                    || dfs(borad, word, x-1, y, i+1) || dfs(borad, word, x, y-1, i+1);
        borad[x][y] -= 128;
        return exist;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<pair<vector<vector<char>>, string>> inputs{
        {
            // board
            {
                {'A', 'B', 'C', 'E'},
                {'S', 'F', 'C', 'S'},
                {'A', 'D', 'E', 'E'}
            },
            // word
            {"ABCCED"}
        },
        {
            {
                {'A', 'B', 'C', 'E'},
                {'S', 'F', 'C', 'S'},
                {'A', 'D', 'E', 'E'}
            },
            {"SEE"}
        },
        {
            {
                {'A', 'B', 'C', 'E'},
                {'S', 'F', 'C', 'S'},
                {'A', 'D', 'E', 'E'}
            },
            {"ABCB"}
        },
        {
            {
                // empty
            },
            {"ABC"}
        }
    };

    for (auto &p : inputs) {
        auto res = s.exist(p.first, p.second);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}