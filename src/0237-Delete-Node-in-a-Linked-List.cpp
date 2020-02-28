/**
 * Write a function to delete a node (except the tail) in a singly linked list, given only access to
 * that node.
 * Given linked list -- head = [4,5,1,9], which looks like following:
 *
 * Example 1:
 * Input: head = [4,5,1,9], node = 5
 * Output: [4,1,9]
 * Explanation: You are given the second node with value 5, the linked list should become 4 -> 1 ->
 * 9 after calling your function.
 *
 * Example 2:
 * Input: head = [4,5,1,9], node = 1
 * Output: [4,5,9]
 * Explanation: You are given the third node with value 1, the linked list should become 4 -> 5 -> 9
 * after calling your function.
 *
 * Note:
 * The linked list will have at least two elements.
 * All of the nodes' values will be unique.
 * The given node will not be the tail and it will always be a valid node of the linked list.
 * Do not return anything from your function.
 */

#include "MyMisc.h"
#include "MyListUtil.h"

#include <iostream>
#include <vector>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    void deleteNode(ListNode* node) {
        auto *next = node->next;
        if (next) {
            node->val = next->val;
            node->next = next->next;
        } else {
            node = nullptr;
        }
        delete next;
    }
};

struct Input {
    ListNode *head;
    ListNode *delNode;
    ListNode *validate;

    Input(std::vector<int> nodes_o, int del_node, std::vector<int> nodes_v) {
        head = myGenerateListWithoutExtraHead(nodes_o);
        delNode = head;
        while (delNode->next && delNode->val != del_node) {
            delNode = delNode->next;
        }
        validate = myGenerateListWithoutExtraHead(nodes_v);
    }
};

int main () {
    Solution sln;

    auto validateList = [](const ListNode *list1, const ListNode *list2) {
        auto *l1 = list1, *l2 = list2;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val != l2->val) {
                std::cout << "FAILED : l1(" << l1->val << "), l2(" << l2->val << ")" << std::endl;
                return false;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        if (l1 == nullptr && l2 == nullptr) {
            std::cout << "PASS!" << std::endl;
            return true;
        }
        std::cout << "Failed : l1 is " << (l1 == nullptr ? "nullptr, " : "not nullptr, ");
        std::cout << "yet l2 is " << (l2 == nullptr ? "nullptr" : "not nullptr") << std::endl;
        return false;
    };

    std::vector<Input> inputs{
        {{4, 5, 1, 9}, 5, {4, 1, 9}},
        {{4, 5, 1, 9}, 1, {4, 5, 9}}
    };

    for (auto &input : inputs) {
        TestCount();
        sln.deleteNode(input.delNode);
        validateList(input.head, input.validate);
    }    
}