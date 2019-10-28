/**
 * Sort a linked list in O(n log n) time using constant space complexity.
 * Example 1:
 * Input: 4->2->1->3
 * Output: 1->2->3->4
 *
 * Example 2:
 * Input: -1->5->3->4->0
 * Output: -1->0->3->4->5
*/

#include "../utils/MyListUtil.h"
#include "../utils/MyMisc.h"

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // partition
        auto fast = head->next, slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        auto mid = slow->next;
        slow->next = nullptr;
        auto left = sortList(head);
        auto right = sortList(mid);

        // merge by sort
        auto h = new ListNode(-1);
        auto res = h;
        while (left != nullptr && right != nullptr) {
            if (left->val < right->val) {
                h->next = left;
                left = left->next;
            } else {
                h->next = right;
                right = right->next;
            }
            h = h->next;
        }
        h->next = left != nullptr ? left : right;
        auto next = res->next;
        delete res;
        return next;
    }
};

int main() {
    Solution s;

    std::vector<std::vector<int>> inputs {
        {4, 2, 1, 3},
        {-1, 5, 3, 4, 0}
    };

    for (auto &input : inputs) {
        TestCount();
        auto *head = myGenerateListWithoutExtraHead(input);
        std::cout << "Original: ";
        myDispList(head);
        auto *sorted = s.sortList(head);
        std::cout << "Sorted  : ";
        myDispList(sorted);
    }
}