/**
 * Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to
 * right, level by level).
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its level order traversal as:
 * [
 *   [3],
 *   [9,20],
 *   [15,7]
 * ]
 */

#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        vector<int> level;
        queue<TreeNode *> nodesQueue;
        auto *levelEndNode = root;
        nodesQueue.emplace(root);
        while (!nodesQueue.empty()) {
            auto *node = nodesQueue.front();
            nodesQueue.pop();
            if (node->left) nodesQueue.emplace(node->left);
            if (node->right) nodesQueue.emplace(node->right);
            level.emplace_back(node->val);
            if (levelEndNode == node) {
                res.emplace_back(level);
                level.clear();
                levelEndNode = nodesQueue.back();
            }
        }
        return res;
    }
};

#define null -1

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> nodesVec{
        {},
        {3, 9, 20, null, null, 15, 7}
    };

    for (auto &nodes : nodesVec) {
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto res = s.levelOrder(root);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &vec : res) {
            std::cout << "    [";
            for (const auto &e : vec) std::cout << e << ", ";
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    }
}