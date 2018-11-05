/**
 * Given inorder and postorder traversal of a tree, construct the binary tree.
 * Note: You may assume that duplicates do not exist in the tree.
 *
 * For example, given
 * inorder = [9,3,15,20,7]
 * postorder = [9,15,7,20,3]
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTreeInternal(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
    }

    TreeNode *buildTreeInternal(vector<int> &inorder, int inorderStart, int inorderEnd,
            vector<int> &postorder, int postorderStart, int postorderEnd) {
        if (inorderStart > inorderEnd || postorderStart > postorderEnd) return nullptr;
        auto *root = new TreeNode(postorder[postorderEnd]);
        int index = inorderStart;
        for (; inorderStart <= inorderEnd && inorder[index] != postorder[postorderEnd]; ++index);
        root->left = buildTreeInternal(inorder, inorderStart, index-1,
                postorder, postorderStart, postorderStart+index-inorderStart-1);
        root->right = buildTreeInternal(inorder, index+1, inorderEnd,
                postorder, postorderStart+index-inorderStart, postorderEnd-1);
        return root;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<pair<vector<int>, vector<int>>> nodesPairs{
        {
            {9, 3, 15, 20, 7},
            {9, 15, 7, 20, 3}
        }
    };

    for (auto &nodesPair : nodesPairs) {
        auto *root = s.buildTree(nodesPair.first, nodesPair.second);
        std::cout << "Case " << testId++ << ": ";
        myDispTreeByLevel(root);
    }
}