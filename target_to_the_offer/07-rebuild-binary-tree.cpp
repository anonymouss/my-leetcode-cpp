/* 输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的
数字。

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

    3
   / \
  9  20
    /  \
   15   7
 
限制：
0 <= 节点个数 <= 5000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
        int p = 0;
        return buildTree_l(preorder, &p, inorder, 0, inorder.size() - 1);
    }

private:
    TreeNode *buildTree_l(std::vector<int> &preorder, int *p,
            std::vector<int> &inorder, int il, int ir) {
        if (il > ir) return nullptr;
        auto *root = new TreeNode{preorder[*p]};
        int in = il;
        for (;in < ir; ++in) {
            if (inorder[in] == preorder[*p]) {
                break;
            }
        }
        ++*p;
        root->left = buildTree_l(preorder, p, inorder, il, in - 1);
        root->right = buildTree_l(preorder, p, inorder, in + 1, ir);
        return root;
    }
};

int main() {
    Solution s;
    std::vector<int> preorder{3, 9, 20, 15, 7};
    std::vector<int> inorder{9, 3, 15, 20, 7};

    auto *root = s.buildTree(preorder, inorder);

    auto preprint = [](auto &&self, TreeNode *root) {
        if (root == nullptr) return;
        std::cout << root->val << " ";
        self(self, root->left);
        self(self, root->right);
    };

    auto inprint = [](auto &&self, TreeNode *root) {
        if (root == nullptr) return; 
        self(self, root->left);
        std::cout << root->val << " ";
        self(self, root->right);
    };

    std::cout << "validate preorder: "; preprint(preprint, root); std::cout << std::endl;
    std::cout << "validate inorder : "; inprint(inprint, root); std::cout << std::endl;
}