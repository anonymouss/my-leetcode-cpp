/* 请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，
每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。
例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。

[["a","b","c","e"],
["s","f","c","s"],
["a","d","e","e"]]

但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入
这个格子。


示例 1：
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true

示例 2：
输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false

提示：
1 <= board.length <= 200
1 <= board[i].length <= 200

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class Solution {
public:
    bool exist(std::vector<std::vector<char>> &board, std::string word) {
        rows = board.size();
        cols = board[0].size(); // assume input valid
        for (auto r = 0; r < rows; ++r) {
            for (auto c = 0; c < cols; ++c) {
                if (dfs(&board, word, r, c, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    int rows, cols;
    bool dfs(std::vector<std::vector<char>> *board, const std::string &word,
            int r, int c, int w) {
        if (c < 0 || r < 0 || c >= cols || r >= rows || (*board)[r][c] != word[w]) {
            return false;
        }
        if (w == word.size() - 1) {
            return true;
        }
        (*board)[r][c] = '0';
        auto res = dfs(board, word, r, c - 1, w + 1) /* left */
                || dfs(board, word, r, c + 1, w + 1) /* right */
                || dfs(board, word, r - 1, c, w + 1) /* up */
                || dfs(board, word, r + 1, c, w + 1); /* down */
        (*board)[r][c] = word[w]; // restore
        return res;
    }
};

int main() {
    Solution s;

    std::vector<std::vector<std::vector<char>>> boards{
        {
            {'A', 'B', 'C', 'E'},
            {'S', 'F', 'C', 'S'},
            {'A', 'D', 'E', 'E'}
        },
        {
            {'a', 'b'},
            {'c', 'd'}
        },
        {
            {'a', 'a'}
        }
    };
    std::vector<std::string> words{"ABCCED", "abcd", "aaa"};

    assert(boards.size() == words.size());
    for (auto i = 0; i < boards.size(); ++i) {
        std::cout << std::boolalpha << s.exist(boards[i], words[i]) << std::endl;
    }
}