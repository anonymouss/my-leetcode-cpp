/* 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入
整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )

示例 1：
输入：
["CQueue","appendTail","deleteHead","deleteHead"]
[[],[3],[],[]]
输出：[null,null,3,-1]
示例 2：

输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]
提示：

1 <= values <= 10000
最多会对 appendTail、deleteHead 进行 10000 次调用

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <stack>
#include <vector>
#include <iostream>
#include <string>
#include <cassert>

// non-thread-safe impl
class CQueue {
public:
    CQueue() = default;

    void appendTail(int value) {
        store.emplace(value);
    }

    int deleteHead() {
        int ret = -1;
        if (fetch.empty()) {
            while (!store.empty()) {
                fetch.emplace(store.top());
                store.pop();
            }
        }
        if (!fetch.empty()) {
            ret = fetch.top();
            fetch.pop();
        }
        return ret;
    }

private:
    std::stack<int> store;
    std::stack<int> fetch;
};

class Machine {
public:
    Machine() : pImpl(nullptr) {};
    virtual ~Machine() {
        reset();
    }

    void perform(const std::vector<std::string> &cmds, const std::vector<std::string> &vals){
        assert(cmds.size() == vals.size());
        for (auto i =  0; i < cmds.size(); ++i) {
            _do(cmds[i], vals[i]);
        }
    }

    void reset() {
        if (pImpl != nullptr) {
            delete pImpl;
            pImpl = nullptr;
            std::cout << std::endl;
        }
    }

private:
    CQueue *pImpl;

    void _do(const std::string &cmd, const std::string &val) {
        if (cmd == "CQueue") {
            if (pImpl != nullptr) delete pImpl;
            pImpl = new CQueue;
            std::cout << "null, ";
        } else {
            assert(pImpl != nullptr);
            if (cmd == "deleteHead") {
                std::cout << pImpl->deleteHead() << ", ";
            } else if (cmd == "appendTail") {
                auto v = std::stoi(val);
                pImpl->appendTail(v);
                std::cout << "null, ";
            }
        }
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */

int main() {
    Machine machine;

    std::vector<std::vector<std::string>> cmds{
        {"CQueue", "appendTail", "deleteHead", "deleteHead"},
        {"CQueue", "deleteHead", "appendTail", "appendTail", "deleteHead", "deleteHead"}
    };
    std::vector<std::vector<std::string>> vals{
        {"", "3", "", ""},
        {"", "", "5", "2", "", ""}
    };

    assert(cmds.size() == vals.size());
    for (auto i = 0; i < cmds.size(); ++i) {
        machine.reset();
        machine.perform(cmds[i], vals[i]);
    }
}