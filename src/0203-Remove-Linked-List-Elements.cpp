/**
 * Remove all elements from a linked list of integers that have value val.
 *
 * Example:
 * Input:  1->2->6->3->4->5->6, val = 6
 * Output: 1->2->3->4->5
 */

#include "MyMisc.h"
#include "MyListUtil.h"

#include <iostream>
#include <vector>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        auto *dumy = new ListNode(0);
        dumy->next = head;
        auto *prev = dumy, *cur = head;
        while (cur != nullptr) {
            if (cur->val == val) {
                prev->next = cur->next;
            } else {
                prev = prev->next;
            }
            if (prev == nullptr) break;
            cur = prev->next;
        }
        auto *newHead = dumy->next;
        delete dumy;
        return newHead;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> nodesv{
        {1, 2, 6, 3, 4, 5, 6},
        {1, 1}
    };
    std::vector<int> valv {6, 1};

    for (auto i = 0; i < nodesv.size(); ++i) {
        TestCount();
        auto *head = myGenerateListWithoutExtraHead(nodesv[i]);
        auto *removed = sln.removeElements(head, valv[i]);
        myDispList(removed);
    }
}