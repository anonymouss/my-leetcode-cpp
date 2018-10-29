/**
 * Given a sorted linked list, delete all duplicates such that each element appear only once.
 *
 * Example 1:
 * Input: 1->1->2
 * Output: 1->2
 *
 * Example 2:
 * Input: 1->1->2->3->3
 * Output: 1->2->3
 */

#include "../utils/MyListUtil.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *pHead = head, *pLeft = head, *pRight = head->next;
        while (pRight != nullptr) {
            if (pRight->val != pLeft->val) {
                pLeft = pLeft->next;
                pLeft->val = pRight->val;
            }
            pRight = pRight->next;
        }

        // cleaning
        auto *p = pLeft->next;
        pLeft->next = nullptr;
        while (p != nullptr) {
            auto *t = p;
            p = p->next;
            delete t;
            t = nullptr;
        }

        return pHead;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> inputs{
        {1, 1, 2},
        {1, 1, 2, 3, 3}
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