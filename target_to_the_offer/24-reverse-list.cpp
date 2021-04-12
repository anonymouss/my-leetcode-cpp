/* 定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

示例:
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL

限制：
0 <= 节点个数 <= 5000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof
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
    ListNode *reverseList(ListNode* head) {
        ListNode *prev = nullptr, *cur = head, *next = nullptr;
        while (cur != nullptr) {
            next = cur->next;
            cur->next = prev;

            prev = cur;
            cur = next;
        }

        return prev;
    }
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

    std::vector<std::vector<int>> inputs{
        {1, 2, 3, 4, 5},
    };

    for (const auto &i : inputs) {
        print_list(s.reverseList(gen_list(i)));
    }
}