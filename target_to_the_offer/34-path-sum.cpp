/* 输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下一直到叶节点所
经过的节点形成一条路径。

示例:
给定如下二叉树，以及目标和 target = 22，
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
返回:
[
   [5,4,11,2],
   [5,8,4,5]
]

提示：
节点总数 <= 10000
注意：本题与主站 113 题相同：https://leetcode-cn.com/problems/path-sum-ii/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    std::vector<std::vector<int>> pathSum(TreeNode *root, int target) {
        std::vector<std::vector<int>> res;
        std::vector<int> path;
        dfs(root, target, &res, &path);
        return res;
    }

private:
    void dfs(TreeNode *node, int target, std::vector<std::vector<int>> *res, std::vector<int> *path) {
        if (!node) return;
        path->emplace_back(node->val);
        target -= node->val;
        if (!node->left && !node->right && target == 0) {
            res->emplace_back(*path);
        } else {
            dfs(node->left, target, res, path);
            dfs(node->right, target, res, path);
        }
        path->erase(path->end() - 1);
    }
};

constexpr int null = -1;

struct Input {
    std::vector<int> vals;
    int target;
};

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

    std::vector<Input> inputs{
        {{5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1}, 22}
    };

    for (const auto &i : inputs) {
        print_v_2d(s.pathSum(gen_tree_from_level(i.vals), i.target));
    }
}