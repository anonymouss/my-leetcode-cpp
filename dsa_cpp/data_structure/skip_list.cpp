/**
 * 跳表
 * https://iq.opengenus.org/skip-list/
 * 底层是一个完成的有序链表，往上各层是底层的有序子集，或者说对下一层的降采样子集。目的就是查找时从上层开始
 * 可以快速缩小查找范围。这，难道不就是二分查找？
 */

#include <iostream>
#include <memory>
#include <vector>
#include <cstdint>
#include <random>
#include <array>

constexpr float     kProbability    = 0.5;
constexpr uint32_t  kMaxLevel       = 4; 

struct Node {
    // 节点值
    int key;
    // 这一层所有节点
    std::vector<std::shared_ptr<Node>> forward;

    Node(int key, uint32_t level) : key(key) {
        for(auto i = 0; i <= level; ++i) {
            forward.emplace_back(nullptr);
        }
    }
};

class SkipList {
public:
    SkipList() {
        mLevel = 0;
        mHeader = std::make_shared<Node>(INT32_MIN, kMaxLevel);
    }

    /**
     * 随机获取跳表某一层，每往上一层，被获取到的几率减小一半
     */
    uint32_t getRandomLevel() const {
        uint32_t level = 0;
        while (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) < kProbability
                && level < kMaxLevel) {
            ++level;
        }
        return level;
    }

    void insert(int key) {
        std::cout << "Insert " << key << std::endl;
        auto cur = mHeader;
        std::array<std::shared_ptr<Node>, kMaxLevel + 1> update;
        update.fill(nullptr);
        for (int i = mLevel; i >= 0; --i) {
            while(cur->forward[i] != nullptr && cur->forward[i]->key < key) {
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        cur = cur->forward[0];

        bool nonExist = (cur == nullptr || cur->key != key);
        if (nonExist) {
            auto level = getRandomLevel();
            if (level > mLevel) {
                for (auto i = mLevel + 1; i < level + 1; ++i) update[i] = mHeader;
                mLevel = level;
            }
            auto node = std::make_shared<Node>(key, level);
            for (int i = 0; i <= level; ++i) {
                node->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = node;
            }
            std::cout << "Inserted " << key << " from 0 to level " << level << std::endl;
        } else {
            std::cout << "Insert key " << key << " is already exist" << std::endl;
        }
    }

    void remove(int key) {
        std::cout << "Remove " << key << std::endl;
        auto cur = mHeader;
        std::array<std::shared_ptr<Node>, kMaxLevel + 1> update;
        update.fill(nullptr);
        for (int i = mLevel; i >= 0; --i) {
            while (cur->forward[i] != nullptr && cur->forward[i]->key < key) cur = cur->forward[i];
            update[i] = cur;
        }
        cur = cur->forward[0];

        bool nonExist = (cur == nullptr || cur->key != key);
        if (!nonExist) {
            for (auto i = 0; i < mLevel; ++i) {
                if (update[i]->forward[i] != cur) break;
                update[i]->forward[i] = cur->forward[i];
            }
            while (mLevel > 0 && mHeader->forward[mLevel] == nullptr) --mLevel;
            std::cout << "Remove key " << key << std::endl;
        } else {
            std::cout << "Remove key " << key << "doesn't exit" << std::endl;
        }
    }

    bool find(int key) const {
        std::cout << "Find " << key << std::endl;
        auto cur = mHeader;
        for (int i = mLevel; i >= 0; --i) {
            while (cur->forward[i] != nullptr && cur->forward[i]->key < key) cur = cur->forward[i];
        }
        cur = cur->forward[0];

        if (cur && cur->key == key) {
            std::cout << "Foud key " << key << std::endl;
            return true;
        } else {
            std::cout << "NotFound key " << key << std::endl;
            return false;
        }
    }

    void display() const {
        std::cout << "Display" << std::endl;
        for (int i = 0; i <= mLevel; ++i) {
            auto cur = mHeader->forward[i];
            std::cout << "Lv" << i << ". : ";
            while (cur) {
                std::cout << cur->key << ", ";
                cur = cur->forward[i];
            }
            std::cout << std::endl;
        }
    }

private:
    uint32_t mLevel;                // 本跳表最高层
    std::shared_ptr<Node> mHeader;  // 头节点指针
};

int main() {
    SkipList list;
    for (auto i = 0; i < 20; ++i) {
        auto v = std::rand() % 10;
        list.insert(v);
    }

    list.display();
    list.remove(5);
    list.display();
}