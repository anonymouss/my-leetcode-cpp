/**
 * Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from
 * left to right, level by level from leaf to root).
 *
 * For example: Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its bottom-up level order traversal as:
 * [
 *   [15,7],
 *   [9,20],
 *   [3]
 * ]
 */

#include "../utils/MyBinaryTreeUtil.h"
#include "../utils/MyContainerUtil.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;
using std::reverse;

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;
        vector<int> level;
        queue<TreeNode *> nodesQueue;
        TreeNode *nodeEndOfLevel = root, *node = nullptr;
        nodesQueue.emplace(root);
        while (!nodesQueue.empty()) {
            node = nodesQueue.front();
            level.emplace_back(node->val);
            nodesQueue.pop();
            if (node->left) nodesQueue.emplace(node->left);
            if (node->right) nodesQueue.emplace(node->right);
            if (node == nodeEndOfLevel) {
                res.emplace_back(level);
                level.clear();
                nodeEndOfLevel = nodesQueue.back();
            }
        }
        reverse(res.begin(), res.end());
        return res;
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
        auto levels = s.levelOrderBottom(root);
        std::cout << "Case " << testId++ << ":\n";
        myDispVector2D(levels);
    }
}