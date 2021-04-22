#include <iostream>
#include <vector>
#include <cassert>
#include <memory>
#include <functional>
#include <cstdint>

template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree() = default;
    bool insert(T value) {
        auto result = insert(root, value);
        if (result) ++tree_size;
        return result;
    }

    bool remove(T value) {
        auto result = remove(root, root, value);
        if (result) {
            assert(tree_size > 0);
            --tree_size;
        }
        return result;
    }

    bool contains(T value) const {
        return contains(root, value);
    }

    bool find_min(T *value) const {
        return find_min(root, value);
    }

    bool find_max(T *value) const {
        return find_max(root, value);
    }

    std::size_t size() const {
        return tree_size;
    }

    std::vector<T> get_elements_inorder() {
        std::vector<T> result;
        traverse_inorder([&](T value) {
            result.emplace_back(value);
        }, root);
        return result;
    }

    std::vector<T> get_elements_preorder() {
        std::vector<T> result;
        traverse_preorder([&](T value) {
            result.emplace_back(value);
        }, root);
        return result;
    }

    std::vector<T> get_elements_postorder() {
        std::vector<T> result;
        traverse_postorder([&](T value) {
            result.emplace_back(value);
        }, root);
        return result;
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
    std::size_t tree_size = 0;

    bool find_max(const std::unique_ptr<Node> &node, T *ret) const {
        if (!node) {
            return false;
        } else if (!node->right) {
            // 无右子树，当前节点就是最大
            *ret = node->value;
            return true;
        }
        return find_max(node->right, ret);
    }

    bool find_min(const std::unique_ptr<Node> &node, T *ret) const {
        if (!node) {
            return false;
        } else if (!node->left) {
            *ret = node->value;
            return true;
        }
        return find_min(node->left, ret);
    }

    bool insert(const std::unique_ptr<Node> &node, T value) {
        if (root == node && !root) {
            // 空树
            root = std::make_unique<Node>(value);
            return true;
        }

        if (value < node->value) {
            // 向左子树插入
            if (!node->left) {
                node->left = std::make_unique<Node>(value);
                return true;
            } else {
                return insert(node->left, value);
            }
        } else if (value > node->value) {
            if (!node->right) {
                node->right = std::make_unique<Node>(value);
                return true;
            } else {
                return insert(node->right, value);
            }
        } else {
            // 这是一个不允许存在重复节点的bst
            return false;
        }
    }

    bool remove(const std::unique_ptr<Node> &parent, const std::unique_ptr<Node> &node, T value) {
        if (!node) {
            return false;
        }

        if (node->value == value) {
            if (node->left && node->right) {
                T v{};
                find_max(node->left, &v);
                remove(root, root, v);
                node->value = v;
                return true;
            } else if (node->left || node->right) {
                auto &nonNull = (node->left ? node->left : node->right);
                if (node == root) {
                    // 首先node就是要被删除的节点，node只有一个子树，自然就是删除后的结果
                    root = std::move(nonNull);
                } else if (value < parent->value) {
                    // 位于左子树
                    parent->left = std::move(nonNull);
                } else {
                    // 位于右子树
                    parent->right = std::move(nonNull);
                }
                return true;
            } else {
                if (node == root) {
                    // 就是空树
                    root = nullptr; // 其实没必要
                } else if (value < parent->value) {
                    // 左子树
                    parent->left = nullptr;
                } else {
                    // 右子树
                    parent->right = nullptr;
                }
                return true;
            }
        } else if (value < node->value) {
            // 继续在左子树寻找
            return remove(node, node->left, value);
        } else {
            // 继续在右子树寻找
            return remove(node, node->right, value);
        }
    }

    bool contains(const std::unique_ptr<Node> &node, T value) const {
        if (!node) {
            return false;
        }
        if (value < node->value) {
            return contains(node->left, value);
        } else if (value > node->value) {
            return contains(node->right, value);
        } else {
            return true;
        }
    }

    void traverse_inorder(std::function<void(T)> callback, const std::unique_ptr<Node> &node) const {
        if (!node) {
            return;
        }

        traverse_inorder(callback, node->left);
        callback(node->value);
        traverse_inorder(callback, node->right);
    }

    void traverse_preorder(std::function<void(T)> callback, const std::unique_ptr<Node> &node) const {
        if (!node) {
            return;
        }

        callback(node->value);
        traverse_preorder(callback, node->left);
        traverse_preorder(callback, node->right);
    }

    void traverse_postorder(std::function<void(T)> callback, const std::unique_ptr<Node> &node) const {
        if (!node) {
            return;
        }

        traverse_inorder(callback, node->left);
        traverse_inorder(callback, node->right);
        callback(node->value);
    }
};

static void test_insert() {
    std::cout << "=== test bst insert ===\n";
    BinarySearchTree<int> bst;
    auto ret = bst.insert(5);
    int min = INT32_MIN, max = INT32_MAX;
    assert(ret);
    assert(bst.size() == 1);
    assert(bst.find_max(&max));
    assert(bst.find_min(&min));
    assert(max == 5);
    assert(min == 5);

    bst.insert(4);
    bst.insert(3);
    bst.insert(6);
    assert(bst.find_max(&max));
    assert(bst.find_min(&min));
    assert(max == 6);
    assert(min == 3);
    assert(bst.size() == 4);

    std::cout << "...insert test ok\n";
}

static void test_remove() {
    std::cout << "=== test bst remove ===\n";
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(4);
    bst.insert(3);
    bst.insert(6);
    int min = INT32_MIN, max = INT32_MAX;
    assert(bst.remove(5));
    assert(bst.find_max(&max));
    assert(bst.find_min(&min));
    assert(max == 6);
    assert(min == 3);
    assert(bst.size() == 3);

    assert(bst.contains(6));
    assert(bst.remove(4));
    assert(bst.remove(3));
    assert(bst.remove(6));
    assert(!bst.remove(5));
    assert(!bst.contains(6));
    assert(bst.size() == 0);

    std::cout << "...remove test ok\n";
}

static void test_contains() {
    std::cout << "=== test bst contains ===\n";
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(4);
    bst.insert(3);
    bst.insert(6);

    assert(bst.contains(5));
    assert(bst.contains(4));
    assert(bst.contains(3));
    assert(bst.contains(6));
    assert(!bst.contains(999));

    std::cout << "...contains test ok\n";
}

using Printer = std::function<void(const std::vector<int> &)>;

static void test_get_elements_preorder(const Printer &print) {
    std::cout << "=== test bst preorder ===\n";
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(4);
    bst.insert(3);
    bst.insert(6);

    std::vector<int> expected = {5, 4, 3, 6};
    std::vector<int> actual = bst.get_elements_preorder();
    print(actual);
    assert(actual == expected);

    std::cout << "...preorder test ok\n";
}

static void test_get_elements_inorder(const Printer &print) {
    std::cout << "=== test bst inorder ===\n";
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(4);
    bst.insert(3);
    bst.insert(6);

    std::vector<int> expected = {3, 4, 5, 6};
    std::vector<int> actual = bst.get_elements_inorder();
    print(actual);
    assert(actual == expected);

    std::cout << "...inorder test ok\n";
}

static void test_get_elements_postorder(const Printer &print) {
    std::cout << "=== test bst postorder ===\n";
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(4);
    bst.insert(3);
    bst.insert(6);

    std::vector<int> expected = {3, 4, 6, 5};
    std::vector<int> actual = bst.get_elements_postorder();
    print(actual);
    assert(actual == expected);

    std::cout << "...postorder test ok\n";
}

int main() {
    test_insert();
    test_remove();
    test_contains();

    auto print = [](const std::vector<int> &vec){
        for (const auto &i : vec) std::cout << i << ", ";
        std::cout << std::endl;
    };

    test_get_elements_preorder(print);
    test_get_elements_inorder(print);
    test_get_elements_postorder(print);
}