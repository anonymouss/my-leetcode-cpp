/* 输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

示例 1：
输入：head = [1,3,2]
输出：[2,3,1]

限制：
0 <= 链表长度 <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof
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
    std::vector<int> reversePrint(ListNode *head) {
        std::vector<int> res;
        auto recursion = [&](auto &&self, ListNode *cur) {
            if (cur == nullptr) return;
            self(self, cur->next);
            res.emplace_back(cur->val);
        };
        recursion(recursion, head);
        return res;
    }
};

int main() {
    Solution s;

    auto genList = [](const std::vector<int> nodes) {
        ListNode *head = nullptr;
        ListNode *prev = nullptr;
        for (const auto &n : nodes) {
            auto *pNode = new ListNode{n};
            if (head == nullptr) {
                head = pNode;
                prev = head;
            } else {
                prev->next = pNode;
                prev = pNode;
            }
        }
        return head;
    };

    auto printVec = [](const std::vector<int> &vec) {
        for (const auto &v : vec) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    };

    printVec(s.reversePrint(genList({1, 3, 2})));
}