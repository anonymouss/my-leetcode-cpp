/**
 * Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct
 * numbers from the original list.
 *
 * Example 1:
 * Input: 1->2->3->3->4->4->5
 * Output: 1->2->5
 *
 * Example 2:
 * Input: 1->1->1->2->3
 * Output: 2->3
 */

#include "../utils/MyListUtil.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *pRealHead = new ListNode(0);
        pRealHead->next = head;
        ListNode *pLeft = pRealHead, *pRight = head;

        while (pRight != nullptr) {
            auto *p_right = pRight;
            if ((pRight->next && pRight->next->val != p_right->val) || pRight->next == nullptr) {
                pLeft->next->val = pRight->val;
                pLeft = pLeft->next;
                pRight = pRight->next;
            } else if (pRight->next) {
                while (pRight->next && pRight->next->val == p_right->val)
                    pRight = pRight->next;
                if (pRight) pRight = pRight->next;
            }
        }

        // cleaning
        auto *left = pLeft->next;
        pLeft->next = nullptr;
        while (left != nullptr) {
            auto *p = left->next;
            delete left;
            left = nullptr;
            left = p;
        }
        auto *pRet = pRealHead->next;
        delete pRealHead; pRealHead = nullptr;

        return pRet;
    }
};

int main() {
        Solution s;
    int testId = 1;

    vector<vector<int>> inputs{
        {1, 2, 3, 3, 4, 4, 5},
        {1, 1, 1, 2, 3}
    };

    for (auto &list : inputs) {
        auto *head = new ListNode(0);
        head->next = nullptr;
        myGenerateList(head, list);
        std::cout << "Case " << testId++ << ":\n";
        std::cout << "Original: ";
        myDispList(head->next);
        std::cout << "Removed:  ";
        auto *p = s.deleteDuplicates(head->next);
        myDispList(p);
    }
}