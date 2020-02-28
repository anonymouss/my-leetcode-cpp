/**
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between
 * two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a
 * node to be a descendant of itself).”
 * Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]
 *
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
 * Output: 3
 * Explanation: The LCA of nodes 5 and 1 is 3.
 *
 * Example 2:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * Output: 5
 * Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according
 * to the LCA definition.
 *
 * Note:
 * All of the nodes' values will be unique.
 * p and q are different and both values will exist in the binary tree.
 */

#include "MyMisc.h"
#include "MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>

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
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == nullptr || root->val == p->val || root->val == q->val) {
            return root;
        }
        auto *left = lowestCommonAncestor(root->left, p, q);
        auto *right = lowestCommonAncestor(root->right, p, q);
        if (left && right) {
            return root;
        } else if (left) {
            return left;
        } else if (right) {
            return right;
        }
        return nullptr;
    }
};

constexpr int null = -1;

struct Input {
    TreeNode *root;
    TreeNode *p;
    TreeNode *q;
    Input(std::vector<int> nodes, int _p, int _q) {
        root = myGenerateTreeFromLeetCodeInput(nodes);
        p = new TreeNode(_p);
        q = new TreeNode(_q);
    }
};

int main() {
    Solution sln;

    std::vector<Input> inputs{
        {{3, 5, 1, 6, 2, 0, 8, null, null, 7, 4}, 5, 1},
        {{3, 5, 1, 6, 2, 0, 8, null, null, 7, 4}, 5, 4}
    };

    for (auto &input : inputs) {
        TestCount();
        std::cout << sln.lowestCommonAncestor(input.root, input.p, input.q)->val << std::endl;
    }
}