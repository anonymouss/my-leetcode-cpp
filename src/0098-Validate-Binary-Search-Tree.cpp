/**
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 * Assume a BST is defined as follows:
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 *
 * Example 1:
 * Input:
 *     2
 *    / \
 *   1   3
 * Output: true
 *
 * Example 2:
 *     5
 *    / \
 *   1   4
 *      / \
 *     3   6
 * Output: false
 * Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
 *              is 5 but its right child's value is 4.
 */

#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;
        stack<TreeNode *> nodesStack;
        auto *node = root;
        int preVal = 0;
        bool isFirstTime = true;
        while (node || !nodesStack.empty()) {
            while (node) {
                nodesStack.emplace(node);
                node = node->left;
            }
            if (!nodesStack.empty()) {
                auto *top = nodesStack.top();
                if (!isFirstTime && top->val <= preVal) return false;
                isFirstTime = false;
                preVal = top->val;
                nodesStack.pop();
                node = top->right;
            }
        }
        return true;
    }
};

#define null -1

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> nodesVec{
        {2, 1, 3},
        {5, 1, 4, null, null, 3, 6}
    };

    for (auto &nodes : nodesVec) {
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto res = s.isValidBST(root);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}