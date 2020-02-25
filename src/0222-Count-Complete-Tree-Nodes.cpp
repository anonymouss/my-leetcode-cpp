/**
 * Given a complete binary tree, count the number of nodes.
 * Note:
 * Definition of a complete binary tree from Wikipedia:
 * In a complete binary tree every level, except possibly the last, is completely filled, and all
 * nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive
 * at the last level h.
 *
 * Example:
 * Input: 
 *     1
 *    / \
 *   2   3
 *  / \  /
 * 4  5 6
 * Output: 6
 */

#include "MyMisc.h"
#include "MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <cmath>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int countNodes(TreeNode *root) {
        if (!root) return 0;
        auto depth = getDepth(root);
        if (depth == 0) return 1;
        auto l = 1, r = static_cast<int>(std::pow(2, depth)) - 1;
        while (l <= r) {
            auto pivot = l + (r - l) / 2;
            if (exist(pivot, depth, root)) {
                l = pivot + 1;
            } else {
                r = pivot - 1;
            }
        }
        return static_cast<int>(std::pow(2, depth)) - 1 + l;
    }

private:
    int getDepth(TreeNode *root) {
        int depth = 0;
        auto *node = root;
        while (node->left) {
            ++depth;
            node = node->left;
        }
        return depth;
    }

    bool exist(int index, int depth, TreeNode *node) {
        auto l = 0, r = static_cast<int>(std::pow(2, depth)) - 1;
        for (auto i = 0; i < depth; ++i) {
            auto pivot = l + (r - l) / 2;
            if (index <= pivot) {
                node = node->left;
                r = pivot;
            } else {
                node = node->right;
                l = pivot + 1;
            }
        }
        return node != nullptr;
    }
};

constexpr int null = -1;

int main() {
    Solution sln;

    std::vector<std::vector<int>> nodesv{
        {1, 2, 3, 4, 5, 6, null},
        {1, 2, 3}
    };

    for (auto &nodes : nodesv) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        std::cout << sln.countNodes(root) << std::endl;
    }
}