/* 请实现两个函数，分别用来序列化和反序列化二叉树。

示例: 
你可以将以下二叉树：

    1
   / \
  2   3
     / \
    4   5

序列化为 "[1,2,3,null,null,4,5]"
注意：本题与主站 297 题相同：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/xu-lie-hua-er-cha-shu-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <string>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:

    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::string serial;
        std::queue<TreeNode *> queue;
        queue.emplace(root);
        while (!queue.empty()) {
            auto *node = queue.front();
            queue.pop();
            serial += (node ? std::to_string(node->val) : "x") + " ";
            if (node) {
                queue.emplace(node->left);
                queue.emplace(node->right);
            }
        }
        return serial;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        std::size_t start = 0, found = data.find(' ', start);
        auto val_str = data.substr(start, found - start);
        if (val_str == "x") return nullptr;
        auto *root = new TreeNode(std::stoi(val_str));
        std::queue<TreeNode *> queue;
        queue.emplace(root);
        while (found != std::string::npos && found != data.length() - 1 /* last space */) {
            start = found + 1;
            found = found = data.find(' ', start);
            auto l_str = data.substr(start, found - start);
            std::string r_str = "x";
            if (found != std::string::npos) {
                start = found + 1;
                found = found = data.find(' ', start);
                r_str = data.substr(start, found - start);
            }
            auto *node = queue.front();
            queue.pop();
            TreeNode *left = nullptr, *right = nullptr;
            if (l_str != "x") {
                left = new TreeNode(std::stoi(l_str));
                queue.emplace(left);
            }
            if (r_str != "x") {
                right = new TreeNode(std::stoi(r_str));
                queue.emplace(right);
            }
            node->left = left;
            node->right = right;
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main() {}