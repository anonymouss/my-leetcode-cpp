#ifndef __UTILS_MY_LIST_UTIL__
#define __UTILS_MY_LIST_UTIL__

#include <iostream>

// defined by leetcode
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
 };

// my util functions
/**
 * @brief Generate a link list from a given array
 *
 * The generated link list starts with a empty head, which doesn't have a valid
 * value (head->val is meaningless), the first actual valid element is head->next
 *
 * @param[out]  list  stores the head of generated link list
 * @param       arr   input array
 * @param       n     valid elements count of link list (array length)
 */
inline void myGenerateList(ListNode *list, int* arr, int n) {
    for(auto i = 0; i < n; ++i) {
        ListNode *node = new ListNode(arr[i]);
        list->next = node;
        list = node;
    }
}

/**
 * @brief Display all element values of a link list from the given start node
 *
 * If input node is head(empty node), it's value(which is invalid) will also be
 * printed.
 *
 * @param   p   start node of the link list
 */
inline void myDispList(ListNode *p) {
    while (p != nullptr) {
        std::cout << p->val << " -> ";
        p = p->next;
    }
    std::cout << std::endl;
};

#endif // __UTILS_MY_LIST_UTIL__