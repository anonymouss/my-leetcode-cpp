#include <iostream>

struct Node {
    int value;
    Node *prev;
    Node *next;

    Node(int v) : value(v), prev(nullptr), next(nullptr) {}
};

class DLinkedList {
public:
    DLinkedList() : first(nullptr), last(nullptr) {}
    void insert(int v) {
        if (first == nullptr) {
            auto *node = new Node(v);
            first = node;
            last = node;
        } else {
            auto *node = new Node(v);
            last->next = node;
            node->prev = last;
            last = node;
        }
    }
    void remove(int v) {
        auto *cur = first;
        while (cur) {
            if (cur->value == v) {
                if (cur->prev && cur->next) {
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                } else if (!cur->prev) {
                    cur->next->prev = nullptr;
                    first = cur->next;
                } else if (!cur->next) {
                    cur->prev->next = nullptr;
                    last = cur->prev;
                }
                delete cur;
                return;
            }
            cur = cur->next;
        }
    }
    bool find(int v) const {
        auto *cur = first;
        while (cur) {
            if (cur->value == v) return true;
            cur = cur->next;
        }
        return false;
    }
    void print() const {
        auto *cur = first;
        while (cur) {
            std::cout << cur->value << " <--> ";
            cur = cur->next;
        }
        std::cout << "null" << std::endl;
    }
    void print_reverse() const {
        auto *cur = last;
        while (cur) {
            std::cout << cur->value << " <--> ";
            cur = cur->prev;
        }
        std::cout << "null" << std::endl;
    }

private:
    Node *first;
    Node *last;
};

int main() {
    DLinkedList list;
    list.insert(1);     // 1
    list.insert(2);     // 1 2
    list.insert(3);     // 1 2 3
    list.print();
    list.print_reverse();
    list.remove(2);     // 1 3
    list.print();
    list.print_reverse();
    list.insert(4);     // 1 3 4
    list.insert(5);     // 1 3 4 5
    list.print();
    list.print_reverse();
    list.remove(1);     // 3 4 5
    list.print();
    list.print_reverse();
    list.remove(5);     // 3 4
    list.print();
    list.print_reverse();
}