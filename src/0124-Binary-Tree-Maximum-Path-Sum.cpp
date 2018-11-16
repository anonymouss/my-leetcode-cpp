/**
 * Given a non-empty binary tree, find the maximum path sum.
 * For this problem, a path is defined as any sequence of nodes from some starting node to any node
 * in the tree along the parent-child connections. The path must contain at least one node and does
 * not need to go through the root.
 *
 * Example 1:
 * Input: [1,2,3]
 *        1
 *       / \
 *      2   3
 * Output: 6
 *
 * Example 2:
 * Input: [-10,9,20,null,null,15,7]
 *    -10
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * Output: 42
 */

#include "../utils/MyMisc.h"
#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;
using std::min;

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int res = INT32_MIN;
        maxPathSumInternal(root, res);
        return res;
    }

    int maxPathSumInternal(TreeNode* root, int &helper) {
        if (!root) return 0;
        int left = max(maxPathSumInternal(root->left, helper), 0);
        int right = max(maxPathSumInternal(root->right, helper), 0);
        helper = max(helper, left + right + root->val);
        return max(left, right) + root->val;
    }
};

#define null -1

int main() {
    Solution s;

    vector<vector<int>> nodesVec{
        {1, 2, 3},
        {-10, 9, 20, null, null, 15, 7},
        {-10, 9, 20, 100, null, 15, 7, null, null, 100},
        {-2, -3, -4},
        {1, -2, -3, 1, 3, -2, null, -1}
    };

    for (auto &nodes : nodesVec) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto sum = s.maxPathSum(root);
        std::cout << sum << std::endl;
    }
}