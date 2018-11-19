/**
 * Given a binary tree, determine if it is height-balanced.
 * For this problem, a height-balanced binary tree is defined as:
 * a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
 *
 * Example 1:
 * Given the following tree [3,9,20,null,null,15,7]:
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * Return true.
 *
 * Example 2:
 * Given the following tree [1,2,2,3,3,null,null,4,4]:
 *        1
 *       / \
 *      2   2
 *     / \
 *    3   3
 *   / \
 *  4   4
 * Return false.
 */

#include "../utils/MyMisc.h"
#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;
using std::abs;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) return true;
        if (abs(getDepth(root->left) - getDepth(root->right)) > 1) return false;
        else return isBalanced(root->left) && isBalanced(root->right);
    }

    int getDepth(TreeNode *root) {
        if (root == nullptr) return 0;
        return 1 + max(getDepth(root->left), getDepth(root->right));
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return checkAndGetDepth(root) != -1;
    }

    int checkAndGetDepth(TreeNode *root) {
        if (root == nullptr) return 0;
        auto leftDepth = checkAndGetDepth(root->left);
        if (leftDepth == -1) return -1;
        auto rightDepth = checkAndGetDepth(root->right);
        if (rightDepth == -1) return -1;
        if (abs(leftDepth - rightDepth) > 1) return -1;
        return 1 + max(leftDepth, rightDepth);
    }
};
#endif

#define null -1

int main() {
    Solution s;

    vector<vector<int>> nodesVec{
        {3, 9, 20, null, null, 15, 7},
        {1, 2, 2, 3, 3, null, null, 4, 4},
        {null}
    };

    for (auto &nodes : nodesVec) {
        TestCount(IOFormat::BOOL);
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto balanced = s.isBalanced(root);
        std::cout << balanced << std::endl;
    }
}