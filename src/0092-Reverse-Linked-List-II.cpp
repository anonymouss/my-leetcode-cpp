/**
 * Reverse a linked list from position m to n. Do it in one-pass.
 * Note: 1 ≤ m ≤ n ≤ length of list.
 *
 * Example:
 * Input: 1->2->3->4->5->NULL, m = 2, n = 4
 * Output: 1->4->3->2->5->NULL
 */

#include "../utils/MyListUtil.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (head == nullptr || head->next == nullptr || m == n) return head;
        auto *pRealHead = new ListNode(0);
        auto *pRightPrev = new ListNode(0);
        pRealHead->next = head;
        auto *pLeftPrev = pRealHead;
        for (int i = 1; i < m; ++i)
            pLeftPrev = pLeftPrev->next;
        pRightPrev->next = pLeftPrev->next;
        for (int i = m; i < n; ++i)
            pRightPrev->next = pRightPrev->next->next;
        for (int i = m; i < n; ++i) {
            auto *pLeft = pLeftPrev->next;
            pLeftPrev->next = pLeft->next;
            pLeft->next = pRightPrev->next->next;
            pRightPrev->next->next = pLeft;
        }

        auto *pRet = pRealHead->next;
        delete pRightPrev; pRightPrev = nullptr;
        delete pRealHead; pRealHead = nullptr;
        return pRet;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> lists{
        {1, 2, 3, 4, 5}
    };

    vector<vector<int>> mns{
        {2, 4}
    };

    if (lists.size() != mns.size()) {
        std::cout << "Incorrect inputs\n";
        return -1;
    }

    ListNode *pHead = new ListNode(0);
    for (int i = 0; i < lists.size(); ++i) {
        pHead->next = nullptr;
        myGenerateList(pHead, lists[i]);
        auto *pRet = s.reverseBetween(pHead->next, mns[i][0], mns[i][1]);
        myDispList(pRet);
    }
}