/**
 * Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
 * Note: Do not modify the linked list.
 * Follow up:
 * Can you solve it without using extra space?
 */

#include "../utils/MyMisc.h"
#include "../utils/MyListUtil.h"

#include <iostream>

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head) return head;
        auto *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                // has circle
                int circleLen = 1;
                fast = fast->next;
                while (fast != slow) {
                    ++circleLen;
                    fast = fast->next;
                }
                slow = fast = head;
                while (circleLen--) fast = fast->next;
                while (fast != slow) {
                    fast = fast->next;
                    slow = slow->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};

int main() {
    std::cout << "no test case for this problem" << std::endl;
}