/**
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
 * An example is the root-to-leaf path 1->2->3 which represents the number 123.
 * Find the total sum of all root-to-leaf numbers.
 * Note: A leaf is a node with no children.
 *
 * Example:
 * Input: [1,2,3]
 *     1
 *    / \
 *   2   3
 * Output: 25
 * Explanation:
 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.
 * Therefore, sum = 12 + 13 = 25.
 *
 * Example 2:
 * Input: [4,9,0,5,1]
 *     4
 *    / \
 *   9   0
 *  / \
 * 5   1
 * Output: 1026
 * Explanation:
 * The root-to-leaf path 4->9->5 represents the number 495.
 * The root-to-leaf path 4->9->1 represents the number 491.
 * The root-to-leaf path 4->0 represents the number 40.
 * Therefore, sum = 495 + 491 + 40 = 1026.
 */

#include "../utils/MyMisc.h"
#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        return sumNumbersInternal(root, 0);
    }

    int sumNumbersInternal(TreeNode *root, int num) {
        if (!root) return 0;
        num = 10 * num + root->val;
        if (!root->left && !root->right) return num; // leaf
        return sumNumbersInternal(root->left, num) + sumNumbersInternal(root->right, num);
    }
};

#define null -1

int main() {
    Solution s;

    vector<vector<int>> nodesVec{
        {1, 2, 3},
        {4, 9, 0, 5, 1}
    };

    for (const auto &nodes : nodesVec) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        auto sum = s.sumNumbers(root);
        std::cout << sum << std::endl;
    }
}