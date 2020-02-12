/**
 * Reverse a singly linked list.
 *
 * Example:
 * Input: 1->2->3->4->5->NULL
 * Output: 5->4->3->2->1->NULL
 *
 * Follow up:
 * A linked list can be reversed either iteratively or recursively. Could you implement both?
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
    ListNode *reverseList(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode *prev = nullptr;
        auto *curr = head;
        auto *next = curr->next;
        while (next) {
            curr->next = prev;
            prev = curr;
            curr = next;
            next = next->next;
        }
        curr->next = prev;
        return curr;
    }
};

int main() {
    Solution sln;
    std::vector<std::vector<int>> inputs{{1, 2, 3, 4, 5}};

    for (auto &input : inputs) {
        TestCount();
        auto *head = myGenerateListWithoutExtraHead(input);
        auto *reversed = sln.reverseList(head);
        myDispList(reversed);
    }
}
