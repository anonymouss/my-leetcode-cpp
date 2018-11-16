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
 * You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every
 * parent has two children).
 *
 * Example:
 * Given the following perfect binary tree,
 *      1
 *    /  \
 *   2    3
 *  / \  / \
 * 4  5  6  7
 * After calling your function, the tree should look like:
 *      1 -> NULL
 *    /  \
 *   2 -> 3 -> NULL
 *  / \  / \
 * 4->5->6->7 -> NULL
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
        TreeLinkNode *parent = root, *current = nullptr;
        while (parent->left) {
            current = parent;
            while (current) {
                current->left->next = current->right;
                if (current->next) current->right->next = current->next->left;
                current = current->next;
            }
            parent = parent->left;
        }
    }
};

#define null -1

int main() {
    Solution s;

    vector<vector<int>> nodesVec{
        {1, 2, 3, 4, 5, 6, 7}
    };

    for (auto &nodes : nodesVec) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput<TreeLinkNode>(nodes);
        s.connect(root);
        // nothing to display
    }
}