/* 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

示例1：
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4

限制：
0 <= 链表长度 <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        ListNode *p1 = nullptr, *p2 = nullptr, *pRetHead = nullptr,
                 *pPre = nullptr;
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

struct Input {
    std::vector<int> vs1;
    std::vector<int> vs2;
};

int main() {
    Solution s;

    auto gen_list = [](const std::vector<int> nodes) {
        ListNode *head = nullptr, *cur = nullptr;
        for (const auto &n : nodes) {
            auto *node = new ListNode(n);
            if (head == nullptr) {
                head = node;
            } else {
                cur->next = node;
            }
            cur = node;
        }
        return head;
    };

    auto print_list = [](const ListNode *const head) {
        auto cur = head;
        while (cur != nullptr) {
            std::cout << cur->val << ", ";
            cur = cur->next;
        }
        std::cout << std::endl;
    };

    std::vector<Input> inputs{
        {{1, 2, 4}, {1, 3, 4}}
    };

    for (const auto &i : inputs) {
        print_list(s.mergeTwoLists(gen_list(i.vs1), gen_list(i.vs2)));
    }
}