/**
 * Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
 *
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
 *
 * Example 1:
 * Input: root = [3,1,4,null,2], k = 1
 *    3
 *   / \
 *  1   4
 *   \
 *    2
 * Output: 1
 *
 * Example 2:
 * Input: root = [5,3,6,2,4,null,null,1], k = 3
 *        5
 *       / \
 *      3   6
 *     / \
 *    2   4
 *   /
 *  1
 * Output: 3
 *
 * Follow up:
 * What if the BST is modified (insert/delete operations) often and you need to find the kth
 * smallest frequently? How would you optimize the kthSmallest routine?
 */

#include "MyMisc.h"
#include "MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <stack>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode *root, int k) {
        std::stack<TreeNode *> st;
        auto *node = root;
        auto count = 0;
        while (node || !st.empty()) {
            while (node) {
                st.emplace(node);
                node = node->left;
            }
            if (!st.empty()) {
                auto *top = st.top();
                ++count;
                if (count == k) return top->val;
                st.pop();
                node = top->right;
            }
        }
        return -1;
    }
};

constexpr int null = -1;

struct Input {
    std::vector<int> nodes;
    int k;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{
        {{3, 1, 4, null, 2}, 1},
        {{5, 3, 6, 2, 4, null, null, 1}, 3}
    };

    for (auto &input : inputs) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(input.nodes);
        std::cout << sln.kthSmallest(root, input.k) << std::endl;
    }
}