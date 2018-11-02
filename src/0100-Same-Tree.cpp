/**
 * Given two binary trees, write a function to check if they are the same or not.
 * Two binary trees are considered the same if they are structurally identical and the nodes have
 * the same value.
 *
 * Example 1:
 * Input:     1         1
 *           / \       / \
 *          2   3     2   3
 *
 *         [1,2,3],   [1,2,3]
 * Output: true
 *
 * Example 2:
 * Input:     1         1
 *           /           \
 *          2             2
 *
 *         [1,2],     [1,null,2]
 * Output: false
 *
 * Example 3:
 * Input:     1         1
 *           / \       / \
 *          2   1     1   2
 *
 *         [1,2,1],   [1,1,2]
 * Output: false
 */

#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
// inorder traverse two trees at the same time, compare each node
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        stack<TreeNode *> pStack, qStack;
        auto *pNode = p, *qNode = q;
        // inorder traverse tree p, update tree q as well
        while (pNode || !pStack.empty()) {
            if (qNode == nullptr && qStack.empty()) return false;
            while (pNode) {
                // tree p is in traversing but tree q get null node, return false
                if (qNode == nullptr) return false;
                pStack.emplace(pNode);
                pNode = pNode->left;
                qStack.emplace(qNode);
                qNode = qNode->left;
            }
            // tree p gets null node, if tree q still has valid node, return false
            if (qNode) return false;
            if (!pStack.empty()) {
                // tree p still have unprocessed nodes, but tree q already finished, return false
                if (qStack.empty()) return false;
                auto *pTop = pStack.top();
                auto *qTop = qStack.top();
                // current traversed nodes from tree p and q have different value, return false
                if (pTop->val != qTop->val) return false;
                pStack.pop();
                qStack.pop();
                pNode = pTop->right;
                qNode = qTop->right;
            }
        }
        // tree p finished, but tree q still have unprocessed nodes, return false
        if (qNode || !qStack.empty()) return false;
        // otherwise, return true
        return true;
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        if (p && q) {
            // if consider p->val != q->val condition first, test runtime will be 4ms.
            // looks like it's because in most test case, most nodes meets p->val == q->val,
            if (p->val == q->val)
                return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
            else
                return false;
        }
        // only one of p and q is valid
        return false;
    }
};
#elif (COMPILE_VERSION == 2)
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<TreeNode *> nodesQueue;
        nodesQueue.emplace(p);
        nodesQueue.emplace(q);
        while(!nodesQueue.empty()) {
            auto *pNode = nodesQueue.front();
            nodesQueue.pop();
            auto *qNode = nodesQueue.front();
            nodesQueue.pop();
            if (!pNode && !qNode) continue;
            if (!pNode || !qNode) return false;
            if (pNode->val != qNode->val) return false;
            nodesQueue.emplace(pNode->left);
            nodesQueue.emplace(qNode->left);
            nodesQueue.emplace(pNode->right);
            nodesQueue.emplace(qNode->right);
        }
        return true;
    }
};
#endif

#define null -1

int main() {
    Solution s;
    int testId = 1;

    vector<vector<vector<int>>> nodesPairs {
        {
            {1, 2, 3},
            {1, 2, 3}
        },
        {
            {1, 2},
            {1, null, 2}
        },
        {
            {1, 2, 1},
            {1, 1, 2}
        },
        {
            {2, null, 4},
            {2, 3, 4}
        }
    };

    for (auto &nodesPair : nodesPairs) {
        auto *p = myGenerateTreeFromLeetCodeInput(nodesPair[0]);
        auto *q = myGenerateTreeFromLeetCodeInput(nodesPair[1]);
        auto isSame = s.isSameTree(p, q);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << isSame << std::endl;
    }
}