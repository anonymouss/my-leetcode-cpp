/* 请完成一个函数，输入一个二叉树，该函数输出它的镜像。

例如输入：
     4
   /   \
  2     7
 / \   / \
1   3 6   9

镜像输出：
     4
   /   \
  7     2
 / \   / \
9   6 3   1

示例 1：
输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]

限制：
0 <= 节点个数 <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <queue>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode *mirrorTree(TreeNode *root) {
        if (root != nullptr) {
            auto *t = root->left;
            root->left = root->right;
            root->right = t;
            mirrorTree(root->left);
            mirrorTree(root->right);
        }
        return root;
    }
};

int main() {
    Solution s;

    auto gen_tree_from_level = [](const std::vector<int> &vals) {
        std::queue<TreeNode *> queue;
        TreeNode *root = nullptr;
        for (auto i = 0; i < vals.size(); ++i) {
            auto *node = new TreeNode(vals[i]);
            if (queue.empty()) {
                root = node;
                queue.emplace(node);
            } else {
                auto *cur = queue.front();
                queue.pop();
                cur->left = node;
                queue.emplace(node);

                if (i < vals.size() - 1) {
                    ++i;
                    auto node2 = new TreeNode(vals[i]);
                    cur->right = node2;
                    queue.emplace(node2);
                }
            }
        }

        return root;
    };

    auto print_tree_preorder = [](TreeNode *head, auto &&self) {
        if (head == nullptr) return;
        std::cout << head->val << ", ";
        self(head->left, self);
        self(head->right, self);
    };

    std::vector<std::vector<int>> inputs{
        {4, 2, 7, 1, 3, 6, 9}
    };

    for (const auto &i : inputs) {
        print_tree_preorder(s.mirrorTree(gen_tree_from_level(i)), print_tree_preorder);
        std::cout << std::endl;
    }
}