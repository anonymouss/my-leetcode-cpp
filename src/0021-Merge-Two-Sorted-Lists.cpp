/**
 * Merge two sorted linked lists and return it as a new list. The new list
 * should be made by
 * splicing together the nodes of the first two lists.
 *
 * Example:
 * Input: 1->2->4, 1->3->4
 * Output: 1->1->2->3->4->4
 */

#include "../utils/MyListUtil.h"

#include <iostream>

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        ListNode *p1 = nullptr, *p2 = nullptr, *pRetHead = nullptr,
                 *pPre = nullptr;
        l1->val < l2->val ? (p1 = l1, p2 = l2) : (p1 = l2, p2 = l1);
        pRetHead = p1;
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->val <= p2->val) {
                pPre = p1;
                p1 = p1->next;
            } else {
                auto *pTmp = p2->next;
                p2->next = p1;
                pPre->next = p2;
                pPre = p2;
                p2 = pTmp;
            }
        }
        if (p1 == nullptr) pPre->next = p2;
        return pRetHead;
    }
};

int main() {
    Solution s;

    int larr1[3] = {1, 2, 4}, rarr1[3] = {1, 3, 4};
    ListNode *llist1 = new ListNode(0), *rlist1 = new ListNode(0);
    myGenerateList(llist1, larr1, 3); myGenerateList(rlist1, rarr1, 3);

    ListNode *llist2 = nullptr, *rlist2 = nullptr;

    std::cout << "Case 1: ";
    myDispList(s.mergeTwoLists(llist1->next, rlist1->next));
    std::cout << "Case 2: ";
    myDispList(s.mergeTwoLists(llist2, rlist2));
}