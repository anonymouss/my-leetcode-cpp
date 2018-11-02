/**
 * Given a binary tree, find its maximum depth.
 * The maximum depth is the number of nodes along the longest path from the root node down to the
 * farthest leaf node.
 * Note: A leaf is a node with no children.
 *
 * Example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its depth = 3.
 */

#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        int depth = 0;
        queue<TreeNode *> nodesQueue;
        nodesQueue.emplace(root);
        auto *nodeEndOfLevel = root;
        while (!nodesQueue.empty()) {
            auto *node = nodesQueue.front();
            nodesQueue.pop();
            if (node->left) nodesQueue.emplace(node->left);
            if (node->right) nodesQueue.emplace(node->right);
            if (nodeEndOfLevel == node) {
                ++depth;
                nodeEndOfLevel = nodesQueue.back();
            }
        }
        return depth;
    }
};

#define null -1

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> nodesVec{
        {3, 9, 20, null, null, 15, 7}
    };

    for (auto &nodes : nodesVec) {
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto depth = s.maxDepth(root);
        std::cout << "Case " << testId++ << ": " << depth << std::endl;
    }
}