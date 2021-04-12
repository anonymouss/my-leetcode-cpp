/* 请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
    1
   / \
  2   2
 / \ / \
3  4 4  3

但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:
    1
   / \
  2   2
   \   \
   3    3

示例 1：
输入：root = [1,2,2,3,4,4,3]
输出：true

示例 2：
输入：root = [1,2,2,null,3,null,3]
输出：false

限制：
0 <= 节点个数 <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/dui-cheng-de-er-cha-shu-lcof
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

constexpr int null = -1;

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == nullptr) return true;
        return is_mirror(root->left, root->right);
    }

private:
    bool is_mirror(TreeNode *a, TreeNode *b) {
        if (!a && !b) return true;
        if (!a || !b || a->val != b->val) return false;
        return is_mirror(a->left, b->right) && is_mirror(a->right, b->left);
    }
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

    std::vector<std::vector<int>> inputs{
        {1, 2, 2, 3, 4, 4, 3},
        {1, 2, 2, null, 3, null, 3}
    };

    for (const auto &i : inputs) {
        // print_tree_preorder(gen_tree_from_level(i), print_tree_preorder); std::cout << std::endl;
        std::cout << std::boolalpha << s.isSymmetric(gen_tree_from_level(i)) << std::endl;
    }
}