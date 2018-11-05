/**
 * Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 * For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of
 * the two subtrees of every node never differ by more than 1.
 *
 * Example:
 * Given the sorted array: [-10,-3,0,5,9],
 * One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
 *       0
 *      / \
 *    -3   9
 *    /   /
 *  -10  5
 */

#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBSTInternal(nums, 0, nums.size()-1);
    }

    TreeNode *sortedArrayToBSTInternal(vector<int> &nums, int start, int end) {
        if (start > end) return nullptr;
        int mid = (start + end + 1) / 2;
        auto root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBSTInternal(nums, start, mid-1);
        root->right = sortedArrayToBSTInternal(nums, mid+1, end);
        return root;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> arrays{
        {-10, -3, 0, 5, 9}
    };

    for (auto &array : arrays) {
        auto *root = s.sortedArrayToBST(array);
        std::cout << "Case " << testId++ << ": ";
        myDispTreeByLevel(root);
    }
}