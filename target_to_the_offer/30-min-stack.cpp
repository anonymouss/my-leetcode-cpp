/* 定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop
的时间复杂度都是 O(1)。

示例:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.min();   --> 返回 -2.
 
提示：
各函数的调用总次数不超过 20000 次

注意：本题与主站 155 题相同：https://leetcode-cn.com/problems/min-stack/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <stack>

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {}
    
    void push(int x) {
        main_stack.push(x);
        if (min_stack.empty() || min_stack.top() >= x) {
            min_stack.push(x);
        }
    }
    
    void pop() {
        if (main_stack.top() == min_stack.top()) {
            min_stack.pop();
        }
        main_stack.pop();
    }
    
    int top() {
        return main_stack.top();
    }
    
    int min() {
        return min_stack.top();
    }

private:
    std::stack<int> main_stack;
    std::stack<int> min_stack;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */

int main() {
    MinStack minStack;
    minStack.push(0);
    minStack.push(1);
    minStack.push(0);
    std::cout << minStack.min() << std::endl;
    minStack.pop();
    std::cout << minStack.top() << std::endl;
    std::cout << minStack.min() << std::endl;
}