/**
 * Implement the following operations of a stack using queues.
 * push(x) -- Push element x onto stack.
 * pop() -- Removes the element on top of the stack.
 * top() -- Get the top element.
 * empty() -- Return whether the stack is empty.
 *
 * Example:
 * MyStack stack = new MyStack();
 * stack.push(1);
 * stack.push(2);  
 * stack.top();   // returns 2
 * stack.pop();   // returns 2
 * stack.empty(); // returns false
 *
 * Notes:
 * You must use only standard operations of a queue -- which means only push to back, peek/pop from
 * front, size, and is empty operations are valid.
 * Depending on your language, queue may not be supported natively. You may simulate a queue by
 * using a list or deque (double-ended queue), as long as you use only standard operations of a
 * queue.
 * You may assume that all operations are valid (for example, no pop or top operations will be
 * called on an empty stack).
 */

#include "MyMisc.h"

#include <iostream>
#include <queue>
#include <vector>
#include <cassert>

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {}
    
    /** Push element x onto stack. */
    void push(int x) {
        if (mQueueA.empty()) {
            mQueueB.emplace(x);
        } else {
            mQueueA.emplace(x);
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        auto *pFull = &mQueueA;
        auto *pEmpty = &mQueueB;
        if (mQueueA.empty()) {
            pFull = &mQueueB;
            pEmpty = &mQueueA;
        }
        while (!pFull->empty()) {
            auto top = pFull->front();
            pFull->pop();
            if (pFull->empty()) {
                return top;
            }
            pEmpty->emplace(top);
        }
        return -1;
    }
    
    /** Get the top element. */
    int top() {
        if (mQueueA.empty()) {
            return mQueueB.back();
        } else {
            return mQueueA.back();
        }
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return mQueueA.empty() && mQueueB.empty();
    }

private:
    std::queue<int> mQueueA;
    std::queue<int> mQueueB;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

int main() {
    MyStack s;
    s.push(1);
    s.push(2);
    assert(s.top() == 2);
    assert(s.pop() == 2);
    assert(s.empty() == false);
    assert(s.pop() == 1);
    assert(s.empty() == true);

    std::cout << "OK, done!" << std::endl;
}