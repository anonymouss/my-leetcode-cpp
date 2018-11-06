/**
 * Given a binary tree, find its minimum depth.
 * The minimum depth is the number of nodes along the shortest path from the root node down to the
 * nearest leaf node.
 * Note: A leaf is a node with no children.
 *
 * Example: Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its minimum depth = 2.
 */

#include "../utils/MyMisc.h"
#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::min;

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        else if (!root->left && !root->right) return 1;
        else if (!root->left) return 1 + minDepth(root->right);
        else if (!root->right) return 1 + minDepth(root->left);
        else return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};

#define null -1

int main() {
    Solution s;

    vector<vector<int>> nodesVec{
        {3, 9, 20, null, null, 15, 7},
        {1, 2}
    };

    for (auto &nodes : nodesVec) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto depth = s.minDepth(root);
        std::cout << depth << std::endl;
    }
}