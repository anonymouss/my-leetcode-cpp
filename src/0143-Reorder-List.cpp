/**
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln,
 * reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 * You may not modify the values in the list's nodes, only nodes itself may be changed.
 *
 * Example 1:
 * Given 1->2->3->4, reorder it to 1->4->2->3.
 *
 * Example 2:
 * Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
 */

#include "../utils/MyMisc.h"
#include "../utils/MyListUtil.h"

#include <iostream>
#include <vector>
#include <deque>

using std::vector;
using std::deque;

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head) return;
        deque<ListNode *> listDeque;
        auto *node = head;
        while (node) {
            listDeque.emplace_back(node);
            node = node->next;
        }
        ListNode *front = nullptr, *back = nullptr;
        while (!listDeque.empty()) {
            front = listDeque.front();
            listDeque.pop_front();
            if (back) back->next = front;
            if (listDeque.empty()) {
                back = nullptr;
            } else {
                back = listDeque.back();
                listDeque.pop_back();
                back->next = nullptr;
            }
            front->next = back;
        }
        return;
    }
};

int main() {
    Solution s;

    vector<vector<int>> nodesVec {
        {1, 2, 3, 4},
        {1, 2, 3, 4, 5}
    };

    for (auto &nodes : nodesVec) {
        auto *head = myGenerateListWithoutExtraHead(nodes);
        std::cout << "original : ";
        myDispList(head);
        s.reorderList(head);
        std::cout << "reordered: ";
        myDispList(head);
    }
}