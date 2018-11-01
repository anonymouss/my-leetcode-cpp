/**
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
 * For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
 *     1
 *    / \
 *   2   2
 *  / \ / \
 * 3  4 4  3
 * But the following [1,2,2,null,3,null,3] is not:
 *     1
 *    / \
 *   2   2
 *    \   \
 *    3    3
 * Note: Bonus points if you could solve it both recursively and iteratively.
 */

#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return isMirror(root, root);
    }

    bool isMirror(TreeNode *p, TreeNode *q) {
        if (!p && !q) return true;
        if (!p || !q) return false;
        return (p->val == q->val) && isMirror(p->left, q->right) && isMirror(p->right, q->left);
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode *> nodesQueue;
        nodesQueue.emplace(root); // tree 1
        nodesQueue.emplace(root); // tree 2
        while (!nodesQueue.empty()) {
            auto *node1 = nodesQueue.front(); // tree 1
            nodesQueue.pop();
            auto *node2 = nodesQueue.front(); // tree 2
            nodesQueue.pop();
            if (!node1 && !node2) continue;
            if (!node1 || !node2) return false;
            if (node1->val != node2->val) return false;
            // should be mirror
            nodesQueue.emplace(node1->left);  // tree 1's left sub-tree
            nodesQueue.emplace(node2->right); // tree 2's right sub-tree
            // should be mirror
            nodesQueue.emplace(node1->right); // tree 1's right sub-tree
            nodesQueue.emplace(node2->left);  // tree 2's left sub-tree
        }
        return true;
    }
};
#endif

#define null -1

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> nodesVec{
        {1, 2, 2, 3, 4, 4, 3},
        {1, 2, 2, null, 3, null, 3}
    };

    for (auto &nodes : nodesVec) {
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto isSym = s.isSymmetric(root);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << isSym << std::endl;
    }
}