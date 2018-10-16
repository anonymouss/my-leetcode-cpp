/**
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list. k is a positive integer and is less than or equal
 * to the length of the linked list. If the number of nodes is not a multiple of
 * k then left-out nodes in the end should remain as it is.
 *
 * Example:
 * Given this linked list: 1->2->3->4->5
 * For k = 2, you should return: 2->1->4->3->5
 * For k = 3, you should return: 3->2->1->4->5
 *
 * Note:
 * Only constant extra memory is allowed.
 * You may not alter the values in the list's nodes, only nodes itself may be
 * changed.
 */

#include "../utils/MyListUtil.h"

#include <iostream>

// delete extra head node and return first valid node
#define RETURN(head) {          \
    auto *node  = head->next;   \
    delete head;                \
    return node;                \
}

class Solution {
public:
    // AC, but ugly codes... need refactor
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k < 2) return head;
        ListNode *pHead = new ListNode(0); // real head.
        pHead->next = head;
        ListNode *pLeft = pHead, *pRight = nullptr;
        ListNode *pPre = nullptr, *pCurrent = nullptr, *pNext = nullptr,
                 *pEnd = nullptr;
        while (pLeft->next != nullptr) {
            pRight = pLeft;
            for (int i = 1; i < k; ++i) {
                // remaning list nodes < k, no need to reverse
                pRight = pRight->next;
                if (pRight->next == nullptr) RETURN(pHead)
            }
            if (pRight == pLeft) RETURN(pHead)
            pPre = pLeft, pCurrent = pPre->next, pNext = pCurrent->next,
            pEnd = pCurrent;
            // std::cout << "Denbug before reverse: "; myDispList(pHead);
            for (int i = 1; i <= k; ++i) {
                if (i == 1) {
                    pPre->next = pRight->next;
                    pCurrent->next = pRight->next->next;
                    pPre = pCurrent;
                    pCurrent = pNext;
                    pNext = pCurrent->next;
                } else {
                    pCurrent->next = pPre;
                    pPre = pCurrent;
                    if (pNext == nullptr) RETURN(pHead)
                    pCurrent = pNext;
                    pNext = pCurrent->next;
                }
            }
            // std::cout << "Denbug reversed: "; myDispList(pHead);
            pLeft = pEnd;
        }
        RETURN(pHead)
    }
};

int main() {
    Solution s;

    int a1[5] = {1, 2, 3, 4, 5};
    ListNode *head1 = new ListNode(0);
    ListNode *head2 = new ListNode(0);
    myGenerateList(head1, a1, 5);
    myGenerateList(head2, a1, 5);

    int a3[2] = {1, 2};
    ListNode *head3 = new ListNode(0);
    myGenerateList(head3, a3, 2);

    std::cout << "Case 1: "; myDispList(s.reverseKGroup(head1->next, 2));
    std::cout << "Case 2: "; myDispList(s.reverseKGroup(head2->next, 3));
    std::cout << "Case 3: "; myDispList(s.reverseKGroup(head3->next, 2));
}