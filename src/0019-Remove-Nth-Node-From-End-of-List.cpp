/**
 * Given a linked list, remove the n-th node from the end of list and return its
 * head.
 *
 * Example:
 * Given linked list: 1->2->3->4->5, and n = 2.
 * After removing the second node from the end, the linked list becomes
 * 1->2->3->5.
 *
 * Note: Given n will always be valid.
 *
 * Follow up: Could you do this in one pass?
 */

#include "../utils/MyListUtil.h"

#include <iostream>

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // meaningless, just indicates the real head
        ListNode *preHead = new ListNode(0);
        auto *p1 = preHead, *p2 = preHead; preHead->next = head;
        while(n-- && p2->next != nullptr) p2 = p2->next;
        while(p2->next != nullptr) {
            p1 = p1->next;
            p2 = p2->next;
        }
        auto *tp = p1->next;
        p1->next = tp == nullptr ? nullptr : tp->next;
        delete tp;
        auto *ret = preHead->next;
        delete preHead;
        return ret;
    }
};

int main() {
    Solution s;

    int a1[5] = {1, 2, 3, 4, 5}, n1 = 2;
    ListNode *l1 = new ListNode(0); myGenerateList(l1, a1, 5);

    int a2[1] = {1}, n2 = 1;
    ListNode *l2 = new ListNode(0); myGenerateList(l2, a2, 1);

    std::cout << "Case 1: "; myDispList(s.removeNthFromEnd(l1->next, n1));
    std::cout << "Case 2: "; myDispList(s.removeNthFromEnd(l2->next, n2));

    // lists will be automatically released after process terminating
}