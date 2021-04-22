#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <memory>
#include <cstdint>
#include <cassert>
#include <stack>

template <typename T>
class AVLTree {
public:
    AVLTree() = default;

    uint32_t getHeight() const {
        get_height_from_node(root);
    }

    T getMin() const { return get_min(root); }
    T getMax() const { return get_max(root); }

    void insert(T value) {
        if (insert(root, value)) {
            ++size;
        }
    }

    void remove(T value) {
        assert(size > 0);
        if (remove(root, value)) {
            --size;
        }
    }

    std::size_t getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    void print() {
        print_level_order();
        print_in_order();
        print_pre_order();
        print_post_order();
    }

private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(T v) {
            value = v;
            left = nullptr;
            right = nullptr;
        }
    };

    std::unique_ptr<Node> root;
    std::size_t size = 0;

    uint32_t get_height_from_node(const std::unique_ptr<Node> &node) const {
        if (!node) return 0;
        return 1 + std::max(get_height_from_node(node->left), get_height_from_node(node->right));
    }

    // 左子树的高度减去右子树的高度
    int32_t get_balance_from(const std::unique_ptr<Node> &node) const {
        return static_cast<int32_t>(get_height_from_node(node->left))
                - static_cast<int32_t>(get_height_from_node(node->right));
    }

    // LL（右旋）：向左子树插入左孩子导致树不平衡，需要右旋转
    // (4)   -insert-      (10)      -result-             (10)
    //                    /                              /
    //                  (7)                            (7)
    //                                                /
    //                                              (4)
    void rotate_right(std::unique_ptr<Node> &y) {
        /**
         *            y
         *           / \
         *          x   t4                         x
         *         / \      --right rotate-->    /  \
         *        z   t3                        z    y
         *       / \                          / \   / \
         *     t1  t2                       t1  t2 t3 t4
         */
        auto x = std::move(y->left);
        auto t3 = std::move(x->right);
        y->left = std::move(t3);
        x->right = std::move(y);
        y = std::move(x);
    }

    // RR（左旋）：向右子树插入右孩子导致树不平衡，需要左旋转
    // (13)   -insert-  (10)    -result-   (10)
    //                     \                  \
    //                    (12)                (12)
    //                                            \
    //                                            (13)
    void rotate_left(std::unique_ptr<Node> &y) {
        /**
         *       y
         *      / \
         *    t4   x                         x
         *        / \   --left rotate-->    /  \
         *      t3  z                      y    z
         *         / \                   / \   / \
         *        t1  t2                t4 t3 t1 t2
         */
        auto x = std::move(y->right);
        auto t3 = std::move(x->left);
        y->right = std::move(t3);
        x->left = std::move(y);
        y = std::move(x);
    }

    /**
     * LR（先左再右旋）：向左子树插入右孩子导致不平衡
     *  (8)  --insert-->     (10)            (10)
     *                       /               /
     *                     (7)             (7)
     *                                       \
     *                                       (8)
     * 
     *          y                                y
     *        /  \                              / \
     *       x    t4                           z  t4
     *      / \      --left rotate x-->       / \       (LL) then right rotate y
     *    t1  z                              x  t3
     *       / \                            / \
     *      t2 t3                         t1  t2
     * 
     * RL（先右旋再左旋）：向右子树插入左孩子导致不平衡
     *  (11)  --insert-->     (10)            (10)
     *                          \                \
     *                          (12)             (12)
     *                                           /
     *                                         (11)
     * 
     *          y                                y
     *        /  \                              / \
     *      t1    x                           t1   z
     *          / \      --right rotate x-->      / \    (RR) then left rotate y
     *         z  t4                            t2   x
     *       / \                                    / \
     *      t2 t3                                 t3  t4
     */

    T get_min(std::unique_ptr<Node> &from) const {
        if (!from->left) return from->value;
        return get_min(from->left);
    }

    T get_max(std::unique_ptr<Node> &from) const {
        if (!from->right) return from->value;
        return get_max(from->right);
    }

    void do_balance(std::unique_ptr<Node> &node) {
        if (node == nullptr) return;
        auto balance = get_balance_from(node);
        if (balance > 1) {
            // 不平衡，且左子树深
            if (get_balance_from(node->left) < 0) {
                // LR
                rotate_left(node->left);
            }
            // LL
            rotate_right(node);
        } else if (balance < -1) {
            // 不平衡，且右子树深
            if (get_balance_from(node->right) > 0) {
                // RL
                rotate_right(node->right);
            }
            // RR
            rotate_left(node);
        }
    }

    bool insert(std::unique_ptr<Node> &node, T value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            return true;
        }
        if (value < node->value) {
            // 往左子树插
            insert(node->left, value);
        } else if (value > node->value) {
            // 往右子树插
            insert(node->right, value);
        } else {
            // 本实现不允许重复元素
            std::cout << "insert value " << value << " already exist" << std::endl;
            return false;
        }

        do_balance(node);
        return true;
    }

    bool remove(std::unique_ptr<Node> &node, T value) {
        if (!node) { return false; }
        if (value < node->value) {
            // 在左子树寻找
            remove(node->left, value);
        } else if (value > node->value) {
            // 在右子树寻找
            remove(node->right, value);
        } else {
            // match
            if (!node->right) {
                // 无右子树/孩子
                node = std::move(node->left);
            } else if (!node->left) {
                // 无左子树/孩子
                node = std::move(node->right);
            } else {
                // 左右子树均存在
                auto v = get_min(node->right);
                std::cout << "min = " << v << std::endl;
                node->value = v;
                remove(node->right, v);
            }
        }
        do_balance(node);
        return true;
    }

    void print_level_order() const {
        assert(root != nullptr);
        std::cout << "[Level Order] ";
        std::queue<Node *> queue;
        queue.emplace(root.get());
        while (!queue.empty()) {
            auto *node = queue.front();
            queue.pop();
            std::cout << node->value << ", ";
            if (node->left) queue.emplace(node->left.get());
            if (node->right) queue.emplace(node->right.get());
        }
        std::cout << std::endl;
    }

    void print_in_order() const {
        assert(root != nullptr);
        std::cout << "[In    Order] ";
        std::stack<Node *> stack;
        auto *node = root.get();
        while (node || !stack.empty()) {
            while (node) {
                stack.emplace(node);
                node = node->left.get();
            }
            if (!stack.empty()) {
                auto *top = stack.top();
                std::cout << top->value << ", ";
                stack.pop();
                node = top->right.get();
            }
        }
        std::cout << std::endl;
    }

    void print_pre_order() const {
        assert(root != nullptr);
        std::cout << "[Pre   Order] ";
        std::stack<Node *> stack;
        auto *node = root.get();
        while (node || !stack.empty()) {
            while (node) {
                std::cout << node->value << ", ";
                stack.emplace(node);
                node = node->left.get();
            }
            if (!stack.empty()) {
                auto *top = stack.top();
                stack.pop();
                node = top->right.get();
            }
        }
        std::cout << std::endl;
    }

    void print_post_order() const {
        assert(root != nullptr);
        std::cout << "[Post  Order] ";
        std::stack<Node *> stack;
        auto *node = root.get();
        Node *last = nullptr;
        while (node || !stack.empty()) {
            if (node) {
                stack.emplace(node);
                node = node->left.get();
            } else {
                auto *top = stack.top();
                if (top->right && top->right.get() != last) {
                    node = top->right.get();
                } else {
                    std::cout << top->value << ", ";
                    stack.pop();
                    last = top;
                }   
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    AVLTree<int> avl;
    for (auto i = 0; i < 5; ++i) avl.insert(i);
    avl.insert(-1);
    avl.insert(-2);
    avl.print();
    //avl.remove(1);
    avl.remove(-2);
    avl.remove(-1);
    avl.remove(0);
    avl.print();
}