// https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/

#include <iostream>
#include <vector>

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = nullptr;
        right = nullptr;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    Node* treeToDoublyList(Node *root) {
        if (!root) return nullptr;
        dfs(root);
        head->left = pre;
        pre->right = head;
        return head;
    }

private:
    Node *head = nullptr, *pre = nullptr;

    void dfs(Node *node) {
        if (!node) return;
        dfs(node->left);
        if (pre) pre->right = node;
        else head = node;
        node->left = pre;
        pre = node;
        dfs(node->right);
    }
};

int main() {}