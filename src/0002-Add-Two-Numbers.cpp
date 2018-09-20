/**
 * You are given two non-empty linked lists representing two non-negative integers. The digits 
 * are stored in reverse order and each of their nodes contain a single digit. Add the two 
 * numbers and return it as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * Example:
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 */

#include <iostream>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
 };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *pHead = new ListNode(0);
        ListNode *pCurrent = pHead;
        auto carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            auto op1 = 0, op2 = 0;
            if (l1 != nullptr) {
                op1 = l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                op2 = l2->val;
                l2 = l2->next;
            }
            auto sum = op1 + op2 + carry;
            carry = sum / 10;
            ListNode *node = new ListNode(sum % 10);
            pCurrent->next = node;
            pCurrent = node;
        }
        auto *ret = pHead->next;
        delete pHead;
        return ret;
    }
};

int main() {
    Solution solution;
    ListNode *l1 = new ListNode(0), *l2 = new ListNode(0); // head doesn't mean anything

    int a1[3] = {2, 4, 3};
    int a2[3] = {5, 6, 4};

    auto generateList = [](ListNode *list, int* arr, int n) {
        for(auto i = 0; i < n; ++i) {
            ListNode *node = new ListNode(arr[i]);
            list->next = node;
            list = node;
        }
    };

    generateList(l1, a1, 3);
    generateList(l2, a2, 3);

    auto* listRes = solution.addTwoNumbers(l1->next, l2->next);

    auto* p = listRes;
    while (p != nullptr) {
        std::cout << p->val << " -> ";
        p = p->next;
    }
    std::cout << std::endl;

    // process terminate, heap will be reclaimed.
}