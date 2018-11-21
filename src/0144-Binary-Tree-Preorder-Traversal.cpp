/**
 * Given a binary tree, return the preorder traversal of its nodes' values.
 *
 * Example:
 * Input: [1,null,2,3]
 *    1
 *     \
 *      2
 *     /
 *    3
 * Output: [1,2,3]
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 */

#include "../utils/MyMisc.h"
#include "../utils/MyBinaryTreeUtil.h"
#include "../utils/MyContainerUtil.h"

#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> preorder;
        if (!root) return preorder;
        stack<TreeNode *> nodesStack;
        nodesStack.emplace(root);
        while (!nodesStack.empty()) {
            auto *node = nodesStack.top();
            nodesStack.pop();
            while (node) {
                preorder.emplace_back(node->val);
                if (node->right) nodesStack.emplace(node->right);
                node = node->left;
            }
        }
        return preorder;
    }
};

#define null -1

int main() {
    Solution s;

    vector<vector<int>> nodesVec {
        {1, null, 2, 3},
        {1, 2, 3, 4, 5, 6, 7}
    };

    for (auto &nodes : nodesVec) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto preorder = s.preorderTraversal(root);
        myDispVector1D(preorder);
    }
}