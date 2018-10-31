/**
 * Given a binary tree, return the inorder traversal of its nodes' values.
 *
 * Example:
 * Input: [1,null,2,3]
 *    1
 *     \
 *      2
 *     /
 *    3
 * Output: [1,3,2]
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 */

#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

#define COMPILE_VERSION 0

#if (COMPILE_VERSION == 0)
// iteration
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
        stack<TreeNode *> nodeStack;
        auto *node = root;
        while (node || !nodeStack.empty()) {
            while (node) {
                // queue left branch
                nodeStack.emplace(node);
                node = node->left;
            }
            // print and queue right
            if (!nodeStack.empty()) {
                auto *top = nodeStack.top();
                nodeStack.pop();
                res.emplace_back(top->val);
                node = top->right;
            }
        }
        return res;
    }
};
#elif (COMPILE_VERSION == 1)
// recrusive
class Solution {
public:
    vector<int> res;
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr) return res;
        if (root->left) {
            inorderTraversal(root->left);
        }
        res.emplace_back(root->val);
        if (root->right) {
            inorderTraversal(root->right);
        }
        return res;
    }
};
#endif

#define null -1

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> nodesVec{
        {1, null, 2, 3},
        {1, 2, 3, 4, 5}
    };

    for (auto &nodes : nodesVec) {
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
#if (COMPILE_VERSION == 1)
        // recrusive solution, clear member res to avoid junk data from last call
        s.res.clear();
#endif
        auto res = s.inorderTraversal(root);
        std::cout << "Case " << testId++ << ": [";
        for (const auto &e : res) std::cout << e << ", ";
        std::cout << "]" << std::endl;
    }
}