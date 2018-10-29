/**
 * Given a linked list and a value x, partition it such that all nodes less than x come before nodes
 * greater than or equal to x.
 * You should preserve the original relative order of the nodes in each of the two partitions.
 *
 * Example:
 * Input: head = 1->4->3->2->5->2, x = 3
 * Output: 1->2->2->4->3->5
 */

#include "../utils/MyListUtil.h"

#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr || head->next == nullptr) return head;
        auto *pRealHead = new ListNode(0);
        pRealHead->next = head;
        auto *pLeftPrev = pRealHead, *pRightPrev = pRealHead;

        // skip the first few nodes which val < x
        while (pRightPrev->next != nullptr && pRightPrev->next->val < x) {
            pLeftPrev = pLeftPrev->next;
            pRightPrev = pRightPrev->next;
        }

        while (pRightPrev->next != nullptr) {
            if (pRightPrev->next->val < x) {
                // disconnect right
                auto *pRight = pRightPrev->next;
                pRightPrev->next = pRight->next;

                // insert to left
                pRight->next = pLeftPrev->next;
                pLeftPrev->next = pRight;

                // update
                pLeftPrev = pRight;
            } else {
                pRightPrev = pRightPrev->next;
            }
        }
        auto *pRet = pRealHead->next;
        delete pRealHead;
        pRealHead = nullptr;
        return pRet;
    }
};

int main() {
    Solution s;
    int testId = 1;

    // head, x
    vector<pair<vector<int>, int>> inputs{
        {
            {1, 4, 3, 2, 5, 2},
            3
        }
    };

    for (auto &p : inputs) {
        std::cout << "Case " << testId++ << ":\n";
        ListNode *pHead = new ListNode(0);
        pHead->next = nullptr;
        myGenerateList(pHead, p.first);
        std::cout << "Orginal : ";
        myDispList(pHead->next);
        auto *pRet = s.partition(pHead->next, p.second);
        std::cout << "After   : ";
        myDispList(pRet);
    }
}