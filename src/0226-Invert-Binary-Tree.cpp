/**
 * Invert a binary tree.
 *
 * Example:
 * Input:
 *      4
 *    /   \
 *   2     7
 *  / \   / \
 * 1   3 6   9
 * Output:
 *      4
 *    /   \
 *   7     2
 *  / \   / \
 * 9   6 3   1
 *
 * Trivia:
 * This problem was inspired by this original tweet by Max Howell:
 * Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary
 * tree on a whiteboard so fuck off.
 */

#include "MyMisc.h"
#include "MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *invertTree(TreeNode *root) {
        if (root == nullptr) {
            return nullptr;
        }
        auto *left = root->left;
        root->left = root->right;
        root->right = left;
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

constexpr int null = -1;

int main() {
    Solution sln;

    std::vector<std::vector<int>> nodesv{
        {4, 2, 7, 1, 3, 6, 9}
    };

    for (auto &nodes : nodesv) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        std::cout << "Before:\n";
        myDispTreeByLevel(root);
        std::cout << "After:\n";
        myDispTreeByLevel(sln.invertTree(root));
    }
}