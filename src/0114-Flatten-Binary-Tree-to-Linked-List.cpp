/**
 * Given a binary tree, flatten it to a linked list in-place.
 * For example, given the following tree:
 *     1
 *    / \
 *   2   5
 *  / \   \
 * 3   4   6
 * The flattened tree should look like:
 * 1
 *  \
 *   2
 *    \
 *     3
 *      \
 *       4
 *        \
 *         5
 *          \
 *           6
 */

#include "../utils/MyMisc.h"
#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    // recursion
    void flatten(TreeNode* root) {
        if (!root) return;
        // process left sub tree first
        if (root->left) flatten(root->left);
        // then process right sub tree
        if (root->right) flatten(root->right);
        // insert left sub tree to right
        auto *right = root->right;
        root->right = root->left;
        root->left = nullptr;
        while (root->right) root = root->right;
        root->right = right;
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    // iteration
    void flatten(TreeNode* root) {
        auto *curNode = root;
        while (curNode) {
            if (curNode->left) {
                auto *right = curNode->left;
                while (right->right) right = right->right;
                right->right = curNode->right;
                curNode->right = curNode->left;
                curNode->left = nullptr;
            }
            curNode = curNode->right;
        }
    }
};
#endif

#define null -1

int main() {
    Solution s;

    vector<vector<int>> nodesVec{
        {1, 2, 5, 3, 4, null, 6}
    };

    for (auto &nodes : nodesVec) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        s.flatten(root);
        myDispTreeByLevel(root);
        myDispTreeInorder(root);
    }
}