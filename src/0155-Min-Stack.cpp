/**
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * push(x) -- Push element x onto stack.
 * pop() -- Removes the element on top of the stack.
 * top() -- Get the top element.
 * getMin() -- Retrieve the minimum element in the stack.
 *
 * Example:
 * MinStack minStack = new MinStack();
 * minStack.push(-2);
 * minStack.push(0);
 * minStack.push(-3);
 * minStack.getMin();   --> Returns -3.
 * minStack.pop();
 * minStack.top();      --> Returns 0.
 * minStack.getMin();   --> Returns -2.
 */

#include "MyMisc.h"

#include <iostream>
#include <stack>

class MinStack {
public:
    void push(int x) {
        st.push(x);
        if (stm.empty() || stm.top() >= x) stm.push(x);
    }

    void pop() {
        int top = st.top();
        st.pop();
        if (top <= stm.top()) stm.pop();
    }

    int top() { return st.top(); }

    int getMin() { return stm.top(); }

private:
    std::stack<int> st;
    std::stack<int> stm;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main() {
    MinStack *minStack = new MinStack();
    minStack->push(-2);
    minStack->push(0);
    minStack->push(-3);
    std::cout << minStack->getMin() << std::endl;
    // Returns - 3.
    minStack->pop();
    std::cout << minStack->top() << std::endl;
    // Returns 0.
    std::cout << minStack->getMin() << std::endl;
    // Returns - 2.
}