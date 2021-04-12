// https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/

#include <iostream>
#include <vector>
#include <unordered_map>

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        if (cache.find(head) == cache.end()) {
            cache[head] = new Node(head->val);
            cache[head]->next = copyRandomList(head->next);
            cache[head]->random = copyRandomList(head->random);
        }
        return cache[head];
    }

private:
    std::unordered_map<Node *, Node *> cache;
};

int main() {}