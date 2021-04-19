#include <iostream>
#include <memory>
#include <string>
#include <cctype>

template <typename T>
struct Node {
    T value;
    std::shared_ptr<Node> next;
    explicit Node (T v = T{}) : value(v), next(nullptr) {}
};

template <typename T>
class LinkedList {
public:
    LinkedList() {
        first = std::make_shared<Node<T>>();
        last = nullptr;
    }

    bool is_empty() const {
        if (last == nullptr) {
            return true;
        } else {
            return false;
        }
    }

    void push_back(T v) {
        if (is_empty()) {
            first->next = std::make_shared<Node<T>>(v);
            last = first->next;
        } else {
            last->next = std::make_shared<Node<T>>(v);
            last = last->next;
        }
    }

    void push_front(T v) {
        if (is_empty()) {
            first->next = std::make_shared<Node<T>>(v);
            last = first->next;
        } else {
            auto node = std::make_shared<Node<T>>(v);
            node->next = first->next;
            first->next = node;
        }
    }

    void erase(T v) {
        if (is_empty()) {
            std::cout << "erase in empty linked list" << std::endl;
            return;
        }
        auto cur = first;
        std::shared_ptr<Node<T>> target = nullptr;
        while (cur != last && cur->next->value != v) {
            cur = cur->next;
        }
        if (cur == last) {
            std::cout << "the node to be erased is not found" << std::endl;
            return;
        }
        target = cur->next;
        cur->next = cur->next->next;
        target.reset();
        if (cur->next == nullptr) {
            last = nullptr;
        }
    }

    std::shared_ptr<Node<T>> find(T v) const {
        if (is_empty()) {
            std::cout << "find in empty linked list" << std::endl;
            return nullptr;
        }
        auto cur = first;
        while (cur != last && cur->next->value != v) {
            cur = cur->next;
        }
        if (cur == last) {
            std::cout << "not found" << std::endl;
            return nullptr;
        }
        return cur->next;
    }

    void reverse() {
        if (is_empty()) {
            std::cout << "reverse in empty linked list" << std::endl;
            return;
        }
        auto cur = first->next;
        std::shared_ptr<Node<T>> prev = first;
        while (cur != nullptr) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        auto second = last;
        last = first->next;
        last->next = nullptr;
        first->next = second;
    }

    void print() const {
        if (is_empty()) {
            std::cout << "print in empty linked list" << std::endl;
            return;
        }
        auto cur = first->next;
        while (cur) {
            std::cout << cur->value << " -> ";
            cur = cur->next;
        }
        std::cout << "null" << std::endl;
    }

private:
    std::shared_ptr<Node<T>> first;
    std::shared_ptr<Node<T>> last;
};

int main() {
    std::cout << "==== Test 1 <int> ===\n";
    LinkedList<int> listi;
    listi.push_back(1);     // 1
    listi.push_back(2);     // 1 2
    listi.push_back(3);     // 1 2 3
    listi.print();
    listi.push_front(4);    // 4 1 2 3
    listi.push_front(5);    // 5 4 1 2 3
    listi.print();
    listi.erase(2);         // 5 4 1 3
    listi.print();
    listi.reverse();
    listi.print();
    std::cout << std::boolalpha << (listi.find(7) == nullptr) << std::endl; // false
    std::cout << std::boolalpha << (listi.find(4) == nullptr) << std::endl; // true

    std::cout << "==== Test 2 <string> ===\n";
    LinkedList<std::string> lists;
    lists.push_back("hello");       // hello
    lists.push_back("world");       // hello world
    lists.push_back("C++");         // hello world C++
    lists.print();
    lists.push_front("2021");       // 2021 hello world C++
    lists.push_front("0416");       // 0416 2021 hello world C++
    lists.print();
    lists.erase("hello");           // 0416 2021 world C++
    lists.print();
    lists.reverse();
    lists.print();
    std::cout << std::boolalpha << (lists.find("java") == nullptr) << std::endl; // false
    std::cout << std::boolalpha << (lists.find("C++") == nullptr) << std::endl; // true
}