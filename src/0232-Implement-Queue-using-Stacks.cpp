/**
 * Implement the following operations of a queue using stacks.
 * push(x) -- Push element x to the back of queue.
 * pop() -- Removes the element from in front of queue.
 * peek() -- Get the front element.
 * empty() -- Return whether the queue is empty.
 *
 * Example:
 * MyQueue queue = new MyQueue();
 * queue.push(1);
 * queue.push(2);  
 * queue.peek();  // returns 1
 * queue.pop();   // returns 1
 * queue.empty(); // returns false
 *
 * Notes:
 * You must use only standard operations of a stack -- which means only push to top, peek/pop from
 * top, size, and is empty operations are valid.
 * Depending on your language, stack may not be supported natively. You may simulate a stack by
 * using a list or deque (double-ended queue), as long as you use only standard operations of a
 * stack.
 * You may assume that all operations are valid (for example, no pop or peek operations will be
 * called on an empty queue).
 */

#include "MyMisc.h"

#include <stack>
#include <iostream>
#include <vector>
#include <cassert>

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {}
    
    /** Push element x to the back of queue. */
    void push(int x) {
        nStack.emplace(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (empty()) {
            // validate
            return -1;
        }
        auto p = peek();
        rStack.pop();
        return p;
    }
    
    /** Get the front element. */
    int peek() {
        if (empty()) {
            // validate
            return -1;
        }
        if (rStack.empty()) {
            while (!nStack.empty()) {
                rStack.emplace(nStack.top());
                nStack.pop();
            }
        }
        return rStack.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return nStack.empty() && rStack.empty();
    }

private:
    std::stack<int> nStack;
    std::stack<int> rStack;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main() {
    MyQueue q;
    q.push(1);
    q.push(2);
    assert(q.peek() == 1);
    assert(q.pop() == 1);
    assert(q.empty() == false);
    assert(q.pop() == 2);
    assert(q.empty() == true);

    std::cout << "OK, done!" << std::endl;
}