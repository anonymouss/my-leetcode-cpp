/**
 * Given a 2D board and a list of words from the dictionary, find all words in the board.
 * Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells
 * are those horizontally or vertically neighboring. The same letter cell may not be used more than
 * once in a word.
 *
 * Example:
 * Input: 
 * board = [
 *   ['o','a','a','n'],
 *   ['e','t','a','e'],
 *   ['i','h','k','r'],
 *   ['i','f','l','v']
 * ]
 * words = ["oath","pea","eat","rain"]
 * Output: ["eat","oath"]
 *
 * Note:
 * All inputs are consist of lowercase letters a-z.
 * The values of words are distinct.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

struct TrieNode {
    std::string content;
    std::vector<TrieNode *> links;
    bool mIsEnd;

    TrieNode() {
        links = std::vector<TrieNode *>(26, nullptr);
        mIsEnd = false;
    }
};

struct TrieTree {
    TrieNode *root;

    TrieTree() {
        root = new TrieNode;
    }

    void insert(std::string word) {
        auto cur = root;
        for (auto w : word) {
            if (cur->links[w - 'a'] == nullptr) {
                cur->links[w - 'a'] = new TrieNode;
            }
            cur = cur->links[w - 'a'];
        }
        cur->mIsEnd = true;
        cur->content = word;
    }
};

class Solution {
public:
    std::vector<std::string> findWords(std::vector<std::vector<char>> &board,
                                        std::vector<std::string> &words) {
        TrieTree trie;
        auto *root = trie.root;
        for (auto word : words) {
            trie.insert(word);
        }
        std::unordered_set<std::string> result;
        auto rows = board.size();
        auto cols = board[0].size();
        std::vector<std::vector<int>> visited(rows, std::vector<int>(cols, 0));
        for (auto r = 0; r < rows; ++r) {
            for (auto c = 0; c < cols; ++c) {
                find(board, visited, r, c, rows, cols, result, root);
            }
        }
        std::vector<std::string> realResult;
        for (auto &r : result) {
            realResult.emplace_back(r);
        }
        return realResult;
    }

private:
    void find(std::vector<std::vector<char>> &board, std::vector<std::vector<int>> &visited,
            int r, int c, int rows, int cols, std::unordered_set<std::string> &result,
            TrieNode *cur) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || visited[r][c] == 1) {
            return;
        }

        cur = cur->links[board[r][c] - 'a'];
        visited[r][c] = 1;
        if (cur == nullptr) {
            visited[r][c] = false;
            return;
        }
        if (cur->mIsEnd) {
            result.emplace(cur->content);
        }
        find(board, visited, r + 1, c, rows, cols, result, cur);
        find(board, visited, r, c + 1, rows, cols, result, cur);
        find(board, visited, r, c - 1, rows, cols, result, cur);
        find(board, visited, r - 1, c, rows, cols, result, cur);
        visited[r][c] = false;
    }
};

struct Input {
    std::vector<std::vector<char>> board;
    std::vector<std::string> words;

    Input(std::vector<std::vector<char>> b, std::vector<std::string> w) : board(b), words(w) {}
};

int main() {
    Solution sln;

    std::vector<Input> inputs{
        {
            {
                {'o','a','a','n'},
                {'e','t','a','e'},
                {'i','h','k','r'},
                {'i','f','l','v'}
            },
            {"oath", "pea", "eat", "rain"}
        }
    };

    auto print_v = [](const std::vector<std::string> &words) {
        std::cout << "[";
        for (const auto &w : words) {
            std::cout << w << ", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &input : inputs) {
        TestCount();
        print_v(sln.findWords(input.board, input.words));
    }
}