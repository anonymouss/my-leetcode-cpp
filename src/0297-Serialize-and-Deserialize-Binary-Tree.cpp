/**
 * Serialization is the process of converting a data structure or object into a sequence of bits so
 * that it can be stored in a file or memory buffer, or transmitted across a network connection link
 * to be reconstructed later in the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how
 * your serialization/deserialization algorithm should work. You just need to ensure that a binary
 * tree can be serialized to a string and this string can be deserialized to the original tree
 * structure.
 *
 * Example: 
 * You may serialize the following tree:
 *     1
 *    / \
 *   2   3
 *      / \
 *     4   5
 * as "[1,2,3,null,null,4,5]"
 *
 * Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not
 * necessarily need to follow this format, so please be creative and come up with different
 * approaches yourself.
 *
 * Note: Do not use class member/global/static variables to store states. Your serialize and
 * deserialize algorithms should be stateless.
 */

#include "MyBinaryTreeUtil.h"
#include "MyMisc.h"

#include <iostream>
#include <queue>
#include <string>
#include <vector>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode *root) {
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
    TreeNode *deserialize(std::string data) {
        std::size_t start = 0, found = data.find(' ', start);
        auto vstr = data.substr(start, found - start);
        if (vstr == "x") return nullptr;
        auto *root = new TreeNode(std::stoi(vstr));
        std::queue<TreeNode *> queue;
        queue.emplace(root);
        while (found != std::string::npos && found != data.length() - 1 /* last space */) {
            start = found + 1;
            found = found = data.find(' ', start);
            auto lstr = data.substr(start, found - start);
            std::string rstr = "x";
            if (found != std::string::npos) {
                start = found + 1;
                found = found = data.find(' ', start);
                rstr = data.substr(start, found - start);
            }
            auto *node = queue.front();
            queue.pop();
            TreeNode *left = nullptr, *right = nullptr;
            if (lstr != "x") {
                left = new TreeNode(std::stoi(lstr));
                queue.emplace(left);
            }
            if (rstr != "x") {
                right = new TreeNode(std::stoi(rstr));
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

constexpr int null = -1;

int main() {
    Codec codec;

    std::vector<std::vector<int>> nodesv{{1, 2, 3, null, null, 4, 5}};
    for (auto &nodes : nodesv) {
        TestCount();
        auto *root = myGenerateTreeFromLeetCodeInput(nodes);
        std::cout << "[original  ]\n";
        myDispTreeByLevel(root);
        auto serial = codec.serialize(root);
        std::cout << "[serialized]\n";
        std::cout << serial << std::endl;
        auto *recovered = codec.deserialize(serial);
        std::cout << "[recovered ]\n";
        myDispTreeByLevel(recovered);
    }
}