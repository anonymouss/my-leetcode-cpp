/**
 * Sort a linked list using insertion sort.
 * A graphical example of insertion sort. The partial sorted list (black) initially contains only
 * the first element in the list.
 * With each iteration one element (red) is removed from the input data and inserted in-place into
 * the sorted list
 *
 * Algorithm of Insertion Sort:
 * - Insertion sort iterates, consuming one input element each repetition, and growing a sorted
 *   output list.
 * - At each iteration, insertion sort removes one element from the input data, finds the location
 *   it belongs within the sorted list, and inserts it there.
 * - It repeats until no input elements remain.
 *
 * Example 1:
 * Input: 4->2->1->3
 * Output: 1->2->3->4
 *
 * Example 2:
 * Input: -1->5->3->4->0
 * Output: -1->0->3->4->5
 */

#include "../utils/MyMisc.h"
#include "../utils/MyListUtil.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        if (!head) return head;
        auto *realHead = new ListNode(INT32_MIN);
        realHead->next = head;
        auto *cur = realHead->next, *pre = realHead;
        while (cur) {
            if (cur->val < pre->val) { // need to insert
                pre->next = cur->next; // disconnect
                auto *t = realHead;
                while (t != pre) { // finding pos to insert
                    if (t->next->val >= cur->val) { //  got it
                        cur->next = t->next;
                        t->next = cur;
                        break;
                    }
                    t = t->next;
                }
                cur = pre->next;
            } else {
                cur = cur->next;
                pre = pre->next;
            }
        }
        auto *ret = realHead->next;
        delete realHead;
        return ret;
    }
};

int main() {
    Solution s;

    vector<vector<int>> nodesVec {
        {4, 2, 1, 3},
        {-1, 0, 3, 4, 5}
    };

    for (auto &nodes : nodesVec) {
        TestCount();
        auto *head = myGenerateListWithoutExtraHead(nodes);
        std::cout << "Original: ";
        myDispList(head);
        auto *sorted = s.insertionSortList(head);
        std::cout << "Sorted  : ";
        myDispList(sorted);
    }
}