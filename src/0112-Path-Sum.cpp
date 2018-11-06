/**
 * Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up
 * all the values along the path equals the given sum.
 *
 * Note: A leaf is a node with no children.
 *
 * Example: Given the below binary tree and sum = 22,
 *       5
 *      / \
 *     4   8
 *    /   / \
 *   11  13  4
 *  /  \      \
 * 7    2      1
 * return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
 */

#include "../utils/MyMisc.h"
#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        if (!root->left && !root->right && root->val == sum) return true; // leaf
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};

#define null -1

int main() {
    Solution s;

    vector<pair<vector<int>, int>> inputs{
        {
            {5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1},
            22
        }
    };

    for (auto &input : inputs) {
        TestCount(true);
        auto *root = myGenerateTreeFromLeetCodeInput(input.first);
        auto res = s.hasPathSum(root, input.second);
        std::cout << res << std::endl;
    }
}