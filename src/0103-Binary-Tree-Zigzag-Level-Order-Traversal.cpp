/**
 * Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left
 * to right, then right to left for the next level and alternate between).
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its zigzag level order traversal as:
 * [
 *   [3],
 *   [20,9],
 *   [15,7]
 * ]
 */

#include "../utils/MyBinaryTreeUtil.h"
#include "../utils/MyContainerUtil.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::reverse;

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        vector<int> level;
        queue<TreeNode *> nodesQueue;
        nodesQueue.emplace(root);
        TreeNode *nodeEndOfLevel = root;
        bool needReverse = false;
        while (!nodesQueue.empty()) {
            auto *node = nodesQueue.front();
            nodesQueue.pop();
            if (node->left) nodesQueue.emplace(node->left);
            if (node->right) nodesQueue.emplace(node->right);
            level.emplace_back(node->val);
            if (nodeEndOfLevel == node) {
                if (needReverse) reverse(level.begin(), level.end());
                res.emplace_back(level);
                level.clear();
                nodeEndOfLevel = nodesQueue.back();
                needReverse = !needReverse;
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
        {3, 9, 20, null, null, 15, 7},
        {1, 2, 3, 4, null, null, 5}
    };

    for (auto &nodes : nodesVec) {
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto res = s.zigzagLevelOrder(root);
        myDispVector2D(res);
    }
}