/* 输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个
节点。例如，一个链表有 6 个节点，从头节点开始，它们的值依次是 1、2、3、4、5、6。这个链表的倒数第 3 个节点是
值为 4 的节点。

示例：
给定一个链表: 1->2->3->4->5, 和 k = 2.
返回链表 4->5.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof
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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        auto *slow = head, *fast = head;
        while (fast != nullptr && k--) {
            fast = fast->next;
        }
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

struct Input {
    std::vector<int> vals;
    int k;
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
        {{1, 2, 3, 4, 5}, 2}
    };

    for (const auto &i : inputs) {
        print_list(s.getKthFromEnd(gen_list(i.vals), i.k));
    }
}