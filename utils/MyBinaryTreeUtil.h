#ifndef __UTILS_MY_BINARY_TREE_UTIL__
#define __UTILS_MY_BINARY_TREE_UTIL__

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using std::vector;
using std::queue;
using std::stack;
using std::to_string;

// defined by leetcode
// normal binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * @brief Generate a binary tree form leetcode format input
 *
 * @param   nodes   leetcode format input
 * @param   null    (optional) indicates to null node in input, -1 in default
 * @return          tree root
 */
inline TreeNode *myGenerateTreeFromLeetCodeInput(const vector<int> &nodes, const int null = -1 /*default*/) {
    if (nodes.empty() || nodes[0] == null) return nullptr;
    auto *root = new TreeNode(nodes[0]);
    queue<TreeNode *> nodeQueue;
    nodeQueue.emplace(root);
    for (int i = 1; i < nodes.size() && !nodeQueue.empty(); i+=2) {
        auto letfVal = nodes[i], rightVal = null;
        if (i + 1 < nodes.size()) rightVal = nodes[i+1];
        // fetch parent node
        auto *pParent = nodeQueue.front();
        nodeQueue.pop();
        TreeNode *pLeft = nullptr, *pRight = nullptr;
        // create children if exist
        if (letfVal != null) {
            pLeft = new TreeNode(letfVal);
            nodeQueue.emplace(pLeft);
        }
        if (rightVal != null) {
            pRight = new TreeNode(rightVal);
            nodeQueue.emplace(pRight);
        }
        pParent->left = pLeft;
        pParent->right = pRight;
    }
    return root;
}

/**
 * @brief display a binary tree by level order
 *
 * @param   root    binary tree root node
 */
inline void myDispTreeByLevel(const TreeNode *root) {
    std::cout << "<level> ";
    queue<const TreeNode *> nodeQueue;
    nodeQueue.emplace(root);
    std::cout << "[";
    while (!nodeQueue.empty()) {
        auto *pParent = nodeQueue.front();
        nodeQueue.pop();
        std::cout << (pParent ? to_string(pParent->val) : "null") << ", ";
        if (pParent) {
            nodeQueue.emplace(pParent->left);
            nodeQueue.emplace(pParent->right);
        }
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief display a binary tree in inorder
 *
 * @param   root    binary tree root node
 */
inline void myDispTreeInorder(const TreeNode *root) {
    std::cout << "<inorder> ";
    stack<const TreeNode *> nodeStack;
    auto *node = root;
    std::cout << "[";
    while (node || !nodeStack.empty()) {
        while (node) {
            nodeStack.emplace(node);
            node = node->left;
        }
        if (!nodeStack.empty()) {
            auto *top = nodeStack.top();
            std::cout << top->val << ", ";
            nodeStack.pop();
            node = top->right;
        }
    }
    std::cout << "]" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// defined by leetcode
// linked binary tree
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

template <typename T>
inline T *myGenerateAnyTreeFromLeetCodeInput(const vector<int> &nodes, const int null = -1 /*default*/) {
    if (nodes.empty() || nodes[0] == null) return nullptr;
    auto *root = new T(nodes[0]);
    queue<T *> nodeQueue;
    nodeQueue.emplace(root);
    for (int i = 1; i < nodes.size() && !nodeQueue.empty(); i+=2) {
        auto letfVal = nodes[i], rightVal = null;
        if (i + 1 < nodes.size()) rightVal = nodes[i+1];
        // fetch parent node
        auto *pParent = nodeQueue.front();
        nodeQueue.pop();
        T  *pLeft = nullptr, *pRight = nullptr;
        // create children if exist
        if (letfVal != null) {
            pLeft = new T (letfVal);
            nodeQueue.emplace(pLeft);
        }
        if (rightVal != null) {
            pRight = new T (rightVal);
            nodeQueue.emplace(pRight);
        }
        pParent->left = pLeft;
        pParent->right = pRight;
    }
    return root;
}

#endif // __UTILS_MY_BINARY_TREE_UTIL__