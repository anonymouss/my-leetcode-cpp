/* 输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
B是A的子结构， 即 A中有出现和B相同的结构和节点值。

例如:
给定的树 A:
     3
    / \
   4   5
  / \
 1   2
给定的树 B：
   4 
  /
 1
返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

示例 1：
输入：A = [1,2,3], B = [3,1]
输出：false

示例 2：
输入：A = [3,4,5,1,2], B = [4,1]
输出：true

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof
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
    bool isSubStructure(TreeNode *A, TreeNode *B) {
        if (A == nullptr || B == nullptr) return false;
        return is_sub_tree(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }

private:
    bool is_sub_tree(TreeNode *pa, TreeNode *pb) {
        if (pb == nullptr) return true;
        if (pa == nullptr) return false;
        if (pa->val == pb->val) {
            return is_sub_tree(pa->left, pb->left) && is_sub_tree(pa->right, pb->right);
        } else {
            return false;
        }
    }
};

struct Input {
    std::vector<int> a_nodes;
    std::vector<int> b_nodes;
};

int main() {
    Solution s;
    std::vector<Input> inputs{
        {{1, 2, 3}, {3, 1}},
        {{3, 4, 5, 1, 2}, {4, 1}}
    };

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


    for (const auto &input : inputs) {
        // print_tree_preorder(gen_tree_from_level(input.a_nodes), print_tree_preorder); std::cout << std::endl;
        // print_tree_preorder(gen_tree_from_level(input.b_nodes), print_tree_preorder); std::cout << std::endl;
        std::cout << std::boolalpha << s.isSubStructure(
            gen_tree_from_level(input.a_nodes), gen_tree_from_level(input.b_nodes)
        ) << std::endl;
    }
}