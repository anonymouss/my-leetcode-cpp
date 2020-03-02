/**
 * Given a binary tree, return all root-to-leaf paths.
 * Note: A leaf is a node with no children.
 *
 * Example:
 * Input:
 *    1
 *  /   \
 * 2     3
 *  \
 *   5
 * Output: ["1->2->5", "1->3"]
 * Explanation: All root-to-leaf paths are: 1->2->5, 1->3
 */

#include "MyMisc.h"
#include "MyBinaryTreeUtil.h"

#include <iostream>
#include <vector>
#include <string>

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
    std::vector<std::string> binaryTreePaths(TreeNode *root) {
        if (!root) {
            return {};
        }
        std::vector<std::string> paths;
        visitTree(&paths, root, std::to_string(root->val));
        return paths;
    }

private:
    void visitTree(std::vector<std::string> *paths, TreeNode *node, std::string path) {
        if (!node->left && !node->right) {
            paths->emplace_back(path);
            return;
        }
        if (node->left) {
            visitTree(paths, node->left, path + "->" + std::to_string(node->left->val));
        }
        if (node->right) {
            visitTree(paths, node->right, path + "->" + std::to_string(node->right->val));
        }
    }
};

constexpr int null = -1;

int main() {
    Solution sln;

    std::vector<std::vector<int>> nodesv{
        {1, 2, 3, null, 5}
    };

    auto print_v = [](const std::vector<std::string> &paths) {
        std::cout << "[";
        for (const auto &path : paths) {
            std::cout << "\"" << path << "\", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &nodes : nodesv) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        print_v(sln.binaryTreePaths(root));
    }
}