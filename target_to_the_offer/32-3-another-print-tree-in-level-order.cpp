/* 请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，
第三行再按照从左到右的顺序打印，其他行以此类推。

例如:
给定二叉树: [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：
[
  [3],
  [20,9],
  [15,7]
]

提示：
节点总数 <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof
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
    std::vector<std::vector<int>> levelOrder(TreeNode *root) {
        std::vector<std::vector<int>> res;
        if (root == nullptr) return {};
        using Element = std::pair<TreeNode *, int /* level */>;
        std::queue<Element> queue;
        queue.emplace(std::make_pair(root, 0));
        int print_level = -1;
        std::vector<int> level_res{};
        while (!queue.empty()) {
            auto e = queue.front();
            queue.pop();
            if (e.second != print_level) {
                if (!level_res.empty()) {
                    res.emplace_back(level_res);
                }
                level_res = std::vector<int>{};
                ++print_level;
            }
            if (print_level % 2 == 0) {
                level_res.emplace_back(e.first->val);
            } else {
                level_res.emplace(level_res.begin(), e.first->val);
            }
            if (e.first->left) queue.push(std::make_pair(e.first->left, e.second + 1));
            if (e.first->right) queue.push(std::make_pair(e.first->right, e.second + 1));
        }
        if (!level_res.empty()) res.emplace_back(level_res);

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

    auto print_v_2d = [](const std::vector<std::vector<int>> &v2d) {
        std::cout << "[\n";
        for (const auto &v : v2d) {
            std::cout << "  [";
            for (const auto &i : v) {
                std::cout << i << ", ";
            }
            std::cout << "]\n";
        }
        std::cout << "]\n";
    };

    std::vector<std::vector<int>> inputs{
        {3, 9, 20, null, null, 15, 7},
        {1, 2, 3, 4, null, null, 5}
    };

    for (const auto &i : inputs) {
        print_v_2d(s.levelOrder(gen_tree_from_level(i)));
    }
}