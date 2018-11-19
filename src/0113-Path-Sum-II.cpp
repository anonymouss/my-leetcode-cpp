/**
 * Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given
 * sum.
 * Note: A leaf is a node with no children.
 *
 * Example: Given the below binary tree and sum = 22,
 *       5
 *      / \
 *     4   8
 *    /   / \
 *   11  13  4
 *  /  \    / \
 * 7    2  5   1
 * Return:
 * [
 *    [5,4,11,2],
 *    [5,8,4,5]
 * ]
 */

#include "../utils/MyMisc.h"
#include "../utils/MyContainerUtil.h"
#include "../utils/MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> pathVec;
        vector<int> sumVec;
        findSumPath(root, sum, pathVec, sumVec);
        return pathVec;
    }

    void findSumPath(TreeNode* root, int sum, vector<vector<int>> &pathVec, vector<int> sumVec) {
        if (!root) return;
        sumVec.emplace_back(root->val);
        sum = sum - root->val;
        if (!root->left && !root->right && sum == 0) pathVec.emplace_back(sumVec);
        else {
            findSumPath(root->left, sum, pathVec, sumVec);
            findSumPath(root->right, sum, pathVec, sumVec);
        }
        sumVec.erase(sumVec.end() - 1);
    }
};

#define null -1

int main() {
    Solution s;

    vector<pair<vector<int>, int>> inputs{
        {
            {5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1},
            22
        }
    };

    for (auto &input : inputs) {
        TestCount(IOFormat::BOOL);
        auto *root = myGenerateTreeFromLeetCodeInput(input.first);
        auto res = s.pathSum(root, input.second);
        myDispVector2D(res);
    }
}