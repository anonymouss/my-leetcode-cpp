/**
 * Given a linked list, swap every two adjacent nodes and return its head.
 *
 * Example:
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 *
 * Note:
 * Your algorithm should use only constant extra space.
 * You may not modify the values in the list's nodes, only nodes itself may be changed.
 */

#include "../utils/MyListUtil.h"

#include <iostream>

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *pRetHead = head->next, *p = head, *pre = nullptr;
        while (p != nullptr && p->next != nullptr) {
            auto *pNext = p->next;
            if (pre != nullptr) pre->next = pNext;
            p->next = pNext->next;
            pNext->next = p;
            pre = p;
            p = p->next;
        }
        return pRetHead;
    }
};

int main() {
    Solution s;

    int arr1[4] = {1, 2, 3, 4};
    ListNode *head1 = new ListNode(0);
    myGenerateList(head1, arr1, 4);

    std::cout << "Case 1: "; myDispList(s.swapPairs(head1->next));
}
