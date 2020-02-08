/**
 * Given a binary tree, imagine yourself standing on the right side of it, return the values of the
 * nodes you can see ordered from top to bottom.
 *
 * Example:
 * Input: [1,2,3,null,5,null,4]
 * Output: [1, 3, 4]
 * Explanation:
 *    1            <---
 *  /   \
 * 2     3         <---
 *  \     \
 *   5     4       <---
 */

#include "MyMisc.h"
#include "MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <queue>
#include <deque>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
// DFS
class Solution {
public:
    std::vector<int> rightSideView(TreeNode *root) {
        std::unordered_map<int, int> rightMostValueAtDepth;
        int maxDepth = -1;
        std::stack<TreeNode *> nodeStack;
        std::stack<int> depthStack;
        nodeStack.emplace(root);
        depthStack.emplace(0);

        while (!nodeStack.empty()) {
            auto *node = nodeStack.top();
            nodeStack.pop();
            auto depth = depthStack.top();
            depthStack.pop();

            if (node != nullptr) {
                maxDepth = std::max(maxDepth, depth);
                if (rightMostValueAtDepth.count(depth) == 0) {
                    rightMostValueAtDepth.emplace(std::make_pair(depth, node->val));
                }
                nodeStack.emplace(node->left);
                nodeStack.emplace(node->right);
                depthStack.emplace(depth + 1);
                depthStack.emplace(depth + 1);
            }
        }
        std::vector<int> rightView;
        for (int depth = 0; depth <= maxDepth; ++depth) {
            rightView.emplace_back(rightMostValueAtDepth[depth]);
        }
        return rightView;
    }
};
#elif (COMPILE_VERSION == 1)
// BFS
class Solution {
public:
    std::vector<int> rightSideView(TreeNode *root) {
        std::unordered_map<int, int> rightMostValueAtDepth;
        int maxDepth = -1;

        std::queue<TreeNode *> nodeQueue;
        std::queue<int> depthQueue;
        nodeQueue.emplace(root);
        depthQueue.emplace(0);

        while (!nodeQueue.empty()) {
            auto *node = nodeQueue.front();
            nodeQueue.pop();
            auto depth = depthQueue.front();
            depthQueue.pop();

            if (node != nullptr) {
                maxDepth = std::max(maxDepth, depth);

                rightMostValueAtDepth.emplace(std::make_pair(depth, node->val));

                nodeQueue.emplace(node->right);
                nodeQueue.emplace(node->left);
                depthQueue.emplace(depth + 1);
                depthQueue.emplace(depth + 1);
            }
        }

        std::vector<int> rightView;
        for (int depth = 0; depth <= maxDepth; ++depth) {
            rightView.emplace_back(rightMostValueAtDepth[depth]);
        }

        return rightView;
    }
};
#endif

constexpr int null = -1;

int main() {
    Solution sln;
    std::vector<std::vector<int>> inputv{
        {1, 2, 3, null, 5, null, 4}
    };

    auto print_v = [](const std::vector<int> &view) {
        std::cout << "[";
        for (const auto &v : view) {
            std::cout << v << ", ";
        }
        std::cout << "]" << std::endl;
    };

    for (const auto &input : inputv) {
        auto *root = myGenerateTreeFromLeetCodeInput(input);
        auto view = sln.rightSideView(root);
        print_v(view);
    }
}