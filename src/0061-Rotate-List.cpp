/**
 * Given a linked list, rotate the list to the right by k places, where k is non-negative.
 *
 * Example 1:
 * Input: 1->2->3->4->5->NULL, k = 2
 * Output: 4->5->1->2->3->NULL
 * Explanation:
 * rotate 1 steps to the right: 5->1->2->3->4->NULL
 * rotate 2 steps to the right: 4->5->1->2->3->NULL
 *
 * Example 2:
 * Input: 0->1->2->NULL, k = 4
 * Output: 2->0->1->NULL
 * Explanation:
 * rotate 1 steps to the right: 2->0->1->NULL
 * rotate 2 steps to the right: 1->2->0->NULL
 * rotate 3 steps to the right: 0->1->2->NULL
 * rotate 4 steps to the right: 2->0->1->NULL
 */

#include "../utils/MyListUtil.h"
#include "../utils/MyClock.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
#ifdef DEBUG
        MyClock<MY_MS> myClock;
#endif
        if (head == nullptr || k == 0) return head;
        vector<ListNode *> listVec;
        auto *p = head;
        while (p != nullptr) {
            listVec.emplace_back(p);
            p = p->next;
        }
        int end = listVec.size() - 1;
        int vTail = end;
        int vHead = 0;
        k = k % listVec.size();
        while (k--) {
            listVec[vTail]->next = listVec[vHead];
            vHead = vTail;
            listVec[--vTail]->next = nullptr;
        }
        return listVec[vHead];
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> lists{
        {1, 2, 3, 4, 5},
        {0, 1, 2},
        {}, // empty
        {1, 2, 3}
    };

    vector<int> ks{2, 4, 0, 2000};

    if (lists.size() != ks.size()) {
        std::cout << "Incorrect test inputs\n";
        return -1;
    }

    ListNode *head = new ListNode(0);
    for (int i = 0; i < lists.size(); ++i) {
        head->next = nullptr;
        myGenerateList(head, lists[i]);
        auto *res = s.rotateRight(head->next, ks[i]);
        std::cout << "Case " << testId++ << ": ";
        myDispList(res);
    }
}