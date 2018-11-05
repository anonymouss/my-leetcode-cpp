/**
 * Given a singly linked list where elements are sorted in ascending order, convert it to a height
 * balanced BST.
 * For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of
 * the two subtrees of every node never differ by more than 1.
 *
 * Example:
 * Given the sorted linked list: [-10,-3,0,5,9],
 * One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
 *       0
 *      / \
 *    -3   9
 *    /   /
 *  -10  5
 */

#include "../utils/MyBinaryTreeUtil.h"
#include "../utils/MyListUtil.h"
#include "../utils/MyMisc.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (head == nullptr) return nullptr;
        auto *node = head;
        int count = 0;
        while (node) {
            ++count;
            node = node->next;
        }
        return sortedListToBSTInternal(&head, 0, count-1);
    }

    TreeNode *sortedListToBSTInternal(ListNode **node, int start, int end) {
        if(start > end) return nullptr;
        int mid = (start + end + 1) / 2;
        auto *pLeft = sortedListToBSTInternal(node, start, mid-1);
        auto *root = new TreeNode((*node)->val);
        *node = (*node)->next;
        root->left = pLeft;
        root->right = sortedListToBSTInternal(node, mid+1, end);
        return root;
    }
};

int main() {
    Solution s;

    vector<vector<int>> nodesVec{
        {-10,-3,0,5,9}
    };

    for (auto &nodes : nodesVec) {
        TestCount();
        auto *head = myGenerateListWithoutExtraHead(nodes);
        auto *root = s.sortedListToBST(head);
        myDispTreeByLevel(root);
    }
}