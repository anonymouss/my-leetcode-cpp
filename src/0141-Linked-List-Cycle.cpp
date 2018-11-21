/**
 * Given a linked list, determine if it has a cycle in it.
 * Follow up:
 * Can you solve it without using extra space?
 */

#include "../utils/MyMisc.h"
#include "../utils/MyListUtil.h"

#include <iostream>

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        auto *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};

int main() {
    std::cout << "no test case for this problem" << std::endl;
}