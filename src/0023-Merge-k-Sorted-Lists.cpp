/**
 * Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
 *
 * Example:
 * Input:
 *   [
 *     1->4->5,
 *     1->3->4,
 *     2->6
 *   ]
 * Output: 1->1->2->3->4->4->5->6
 */

#include "../utils/MyListUtil.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    // Based on problem 0021-Merge-Two-Sorted-Lists
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        for (int i = 0; i < lists.size() - 1; i += 2) {
            auto *p1 = lists[i], *p2 = lists[i + 1];
            lists.emplace_back(mergeTwoLists(p1, p2));
        }
        return lists.back();
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        ListNode *p1 = nullptr, *p2 = nullptr, *pRetHead = nullptr, *pPre = nullptr;
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

int  main() {
    Solution s;

    vector<ListNode*> lists1;
    int arr11[3] = {1, 4, 5}, arr12[3] = {1, 3, 4}, arr13[2] = {2, 6};
    ListNode *l11 = new ListNode(0), *l12 = new ListNode(0), *l13 = new ListNode(0);
    myGenerateList(l11, arr11, 3), myGenerateList(l12, arr12, 3), myGenerateList(l13, arr13, 2);
    lists1.emplace_back(l11->next); lists1.emplace_back(l12->next); lists1.emplace_back(l13->next);

    std::cout << "Case 1: "; myDispList(s.mergeKLists(lists1));
}