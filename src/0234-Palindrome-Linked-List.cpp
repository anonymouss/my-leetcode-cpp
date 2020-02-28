/**
 * Given a singly linked list, determine if it is a palindrome.
 *
 * Example 1:
 * Input: 1->2
 * Output: false
 *
 * Example 2:
 * Input: 1->2->2->1
 * Output: true
 *
 * Follow up:
 * Could you do it in O(n) time and O(1) space?
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
    bool isPalindrome(ListNode* head) {
        if (head == nullptr) return true;
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *prev = nullptr;
        auto *cur = slow->next;
        while (cur) {
            auto *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        auto *left = head, *right = prev;
        while (right) {
            if (left->val != right->val) return false;
            left = left->next;
            right = right->next;
        }
        // need to restore list
        return true;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> nodesv{
        {1, 2}, {1, 2, 2, 1}
    };

    for (auto &nodes : nodesv) {
        TestCount(IOFormat::BOOL);
        auto *head = myGenerateListWithoutExtraHead(nodes);
        std::cout << sln.isPalindrome(head) << std::endl;
    }
}