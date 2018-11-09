/**
 * Given a binary tree
 * struct TreeLinkNode {
 *   TreeLinkNode *left;
 *   TreeLinkNode *right;
 *   TreeLinkNode *next;
 * }
 * Populate each next pointer to point to its next right node. If there is no next right node, the
 * next pointer should be set to NULL.
 * Initially, all next pointers are set to NULL.
 *
 * Note:
 * You may only use constant extra space.
 * Recursive approach is fine, implicit stack space does not count as extra space for this problem.
 *
 * Example:
 * Given the following binary tree,
 *      1
 *    /  \
 *   2    3
 *  / \    \
 * 4   5    7
 * After calling your function, the tree should look like:
 *      1 -> NULL
 *    /  \
 *   2 -> 3 -> NULL
 *  / \    \
 * 4-> 5 -> 7 -> NULL
 */

#include "../utils/MyMisc.h"
#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root) return;
        TreeLinkNode *dummy = new TreeLinkNode(0), *t = dummy;
        while (root) {
            if (root->left) {
                t->next = root->left;
                t = t->next;
            }
            if (root->right) {
                t->next = root->right;
                t = t->next;
            }
            root = root->next;
            if (!root) {
                t = dummy;
                root = dummy->next;
                dummy->next = nullptr;
            }
        }
    }
};

#define null -1

int main() {
    Solution s;

    vector<vector<int>> nodesVec{
        {1, 2, 3, 4, 5, null, 7}
    };

    for (auto &nodes : nodesVec) {
        TestCount();
        auto *root = myGenerateAnyTreeFromLeetCodeInput<TreeLinkNode>(nodes);
        s.connect(root);
        // nothing to display
    }
}