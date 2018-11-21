/**
 * A linked list is given such that each node contains an additional random pointer which could
 * point to any node in the list or null.
 * Return a deep copy of the list.
 */

#include "../utils/MyMisc.h"
#include "../utils/MyListUtil.h"

#include <iostream>
#include <unordered_map>

using std::unordered_map;

class Solution {
public:
    unordered_map<RandomListNode *, RandomListNode *> hash;

    // very semilar to problem #133 - clone graph
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head) return head;
        if (hash.find(head) == hash.end()) {
            hash[head] = new RandomListNode(head->label);
            hash[head]->next = copyRandomList(head->next);
            hash[head]->random = copyRandomList(head->random);
        }
        return hash[head];
    }
};

int main() {
    std::cout << "No test case for this problem" << std::endl;
}