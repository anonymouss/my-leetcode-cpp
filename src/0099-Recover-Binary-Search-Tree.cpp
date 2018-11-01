/**
 * Two elements of a binary search tree (BST) are swapped by mistake.
 * Recover the tree without changing its structure.
 *
 * Example 1:
 * Input: [1,3,null,null,2]
 *    1
 *   /
 *  3
 *   \
 *    2
 * Output: [3,1,null,null,2]
 *    3
 *   /
 *  1
 *   \
 *    2
 *
 * Example 2:
 * Input: [3,1,4,null,null,2]
 *   3
 *  / \
 * 1   4
 *    /
 *   2
 * Output: [2,1,4,null,null,3]
 *   2
 *  / \
 * 1   4
 *    /
 *   3
 *
 * Follow up:
 * A solution using O(n) space is pretty straight forward.
 * Could you devise a constant space solution?
 */

#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::swap;

// This problem only has two mis-swapped elements, solution is find them and swap back
// for bst, inorder traversal is in ascending order, it's easy to find these two elements by inorder
// traversal. The difficulty is problem requires a solution in constant space complexity
// morris traversal is in o(1) space
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *first = nullptr, *second = nullptr, *parent = nullptr;
        TreeNode *cur = root, *pre = nullptr;
        while (cur) {
            if (cur->left == nullptr) {
                if (parent && parent->val > cur->val) {
                    if (first == nullptr) first = parent;
                    second = cur;
                }
                parent = cur;
                //std::cout << cur->val << std::endl;
                cur = cur->right;
            } else {
                pre = cur->left;
                while (pre->right && pre->right != cur)
                    pre = pre->right;
                if (pre->right == nullptr) {
                    pre->right = cur;
                    cur = cur->left;
                } else {
                    pre->right = nullptr;
                    if (parent->val > cur->val) {
                        if (first == nullptr) first = parent;
                        second = cur;
                    }
                    parent = cur;
                    //std::cout << cur->val << std::endl;
                    cur = cur->right;
                }
            }
        }
        if (first && second) swap(first->val, second->val);
    }
};

#define null -1

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> nodesVec{
        {1, 3, null, null, 2},
        {3, 1, 4, null, null, 2}
    };

    for (auto &nodes : nodesVec) {
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        std::cout << "Case " << testId++ << ":\n";
        std::cout << "  Original:  ";
        myDispTreeInorder(root);
        s.recoverTree(root);
        std::cout << "  Recovered: ";
        myDispTreeInorder(root);
    }
}