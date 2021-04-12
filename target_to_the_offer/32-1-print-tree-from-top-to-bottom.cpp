/* 从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

例如:
给定二叉树: [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
返回：
[3,9,20,15,7]

提示：
节点总数 <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-lcof
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
    std::vector<int> levelOrder(TreeNode *root) {
        std::vector<int> res;
        if (root == nullptr) return res;
        std::queue<TreeNode *> queue;
        queue.emplace(root);
        while (!queue.empty()) {
            auto *node = queue.front();
            queue.pop();
            res.emplace_back(node->val);
            if (node->left) queue.emplace(node->left);
            if (node->right) queue.emplace(node->right);
        }
        return res;
    }
};

constexpr int null = -1;

int main() {
    Solution s;

    auto gen_tree_from_level = [&](const std::vector<int> &vals) {
        std::queue<TreeNode *> queue;
        TreeNode *root = nullptr;
        for (auto i = 0; i < vals.size(); ++i) {
            TreeNode *node = nullptr;
            if (vals[i] != null)
                node = new TreeNode(vals[i]);
            if (queue.empty()) {
                root = node;
                if (node)
                    queue.emplace(node);
            } else {
                auto *cur = queue.front();
                queue.pop();
                cur->left = node;
                if (node)
                    queue.emplace(node);

                if (i < vals.size() - 1) {
                    ++i;
                    TreeNode *node2 = nullptr;
                    if (vals[i] != null) {
                        node2 = new TreeNode(vals[i]);
                        cur->right = node2;
                        queue.emplace(node2);
                    } else {
                        cur->right = nullptr;
                    }
                }
            }
        }

        return root;
    };

    auto print_tree_preorder = [&](TreeNode *head, auto &&self) {
        if (head == nullptr) {
            std::cout << "null, ";
            return;
        }
        std::cout << head->val << ", ";
        self(head->left, self);
        self(head->right, self);
    };

    auto print_v = [](const std::vector<int> &v) {
        for (const auto &i : v) std::cout << i << ", ";
        std::cout << std::endl;
    };

    std::vector<std::vector<int>> inputs{
        {3, 9, 20, null, null, 15, 7}
    };

    for (const auto &i : inputs) {
        print_v(s.levelOrder(gen_tree_from_level(i)));
    }
}