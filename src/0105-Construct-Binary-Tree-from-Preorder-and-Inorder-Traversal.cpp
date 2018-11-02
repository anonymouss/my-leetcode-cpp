/**
 * Given preorder and inorder traversal of a tree, construct the binary tree.
 * Note: You may assume that duplicates do not exist in the tree.
 *
 * For example, given
 * preorder = [3,9,20,15,7]
 * inorder = [9,3,15,20,7]
 * Return the following binary tree:
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 */

#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Solution {
public:
    int rootIndex = 0;

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        rootIndex = 0;
        return buildTreeInternal(preorder, rootIndex, inorder, 0, inorder.size()-1);
    }

    TreeNode *buildTreeInternal(vector<int> &preorder, int &preorderIdx,
            vector<int> &inorder, int inorderStart, int inorderEnd) {
        if (inorderStart > inorderEnd || preorderIdx >= preorder.size()) return nullptr;
        auto *root = new TreeNode(preorder[preorderIdx]);
        int index = inorderStart;
        for (; index <= inorderEnd && inorder[index] != preorder[preorderIdx]; ++index);
        ++preorderIdx;
        // create left sub-tree
        root->left = buildTreeInternal(preorder, preorderIdx, inorder, inorderStart, index-1);
        // create right sub-tree
        root->right = buildTreeInternal(preorder, preorderIdx, inorder, index+1, inorderEnd);
        return root;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<pair<vector<int>, vector<int>>> nodesPairs{
        {
            {3, 9, 20, 15, 7},
            {9, 3, 15, 20, 7}
        },
        {
            {1, 2, 3},
            {1, 2, 3}
        },
        {
            {3, 1, 2, 4},
            {1, 2, 3, 4}
        }
    };

    for (auto &nodesPair : nodesPairs) {
        auto *root = s.buildTree(nodesPair.first, nodesPair.second);
        std::cout << "Case " << testId++ << ": ";
        myDispTreeByLevel(root);
    }
}