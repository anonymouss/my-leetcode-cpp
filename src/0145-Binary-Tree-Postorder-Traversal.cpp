/**
 * Given a binary tree, return the postorder traversal of its nodes' values.
 *
 * Example:
 * Input: [1,null,2,3]
 *    1
 *     \
 *      2
 *     /
 *    3
 * Output: [3,2,1]
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> postorder;
        if (!root) return postorder;
        stack<TreeNode *> nodesStack;
        nodesStack.emplace(root);
        auto *last = root;
        while (!nodesStack.empty()) {
            auto *node = nodesStack.top();
            if (!node->left && !node->right || node->left == last || node->right == last) {
                postorder.emplace_back(node->val);
                nodesStack.pop();
                last = node;
            } else {
                if (node->right) nodesStack.emplace(node->right);
                if (node->left) nodesStack.emplace(node->left);
            }

        }
        return postorder;
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
        auto postorder = s.postorderTraversal(root);
        myDispVector1D(postorder);
    }
}