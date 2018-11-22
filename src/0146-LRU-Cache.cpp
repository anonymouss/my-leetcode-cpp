/**
 * Design and implement a data structure for Least Recently Used (LRU) cache. It should support the
 * following operations: get and put.
 * get(key) - Get the value (will always be positive) of the key if the key exists in the cache,
 * otherwise return -1.
 * put(key, value) - Set or insert the value if the key is not already present. When the cache
 * reached its capacity, it should invalidate the least recently used item before inserting a new item.
 *
 * Follow up: Could you do both operations in O(1) time complexity?
 *
 * Example:
 * LRUCache cache = new LRUCache( 2 ); // param: capacity
 * cache.put(1, 1);
 * cache.put(2, 2);
 * cache.get(1);       // returns 1
 * cache.put(3, 3);    // evicts key 2
 * cache.get(2);       // returns -1 (not found)
 * cache.put(4, 4);    // evicts key 1
 * cache.get(1);       // returns -1 (not found)
 * cache.get(3);       // returns 3
 * cache.get(4);       // returns 4
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <list>

using std::vector;
using std::unordered_map;
using std::pair;
using std::list;

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

#ifndef DEBUG
#define DEBUG
#endif // DEBUG

class LRUCache {
public:
    LRUCache(int capacity) : mCapacity(capacity) {}
    
    int get(int key) {
        auto itr = mCacheMap.find(key);
        if (itr == mCacheMap.end()) return -1; // not fount
        mCacheList.splice(mCacheList.begin(), mCacheList, itr->second);
        return itr->second->second;
    }
    
    void put(int key, int value) {
        auto itr = mCacheMap.find(key);
        if (itr != mCacheMap.end()) mCacheList.erase(itr->second);
        mCacheList.emplace_front(pair<int, int>{key, value});
        mCacheMap[key] = mCacheList.begin();
        if (mCacheList.size() > mCapacity) { // exceeds capacity
            auto k = mCacheList.back().first;
            mCacheMap.erase(k);
            mCacheList.pop_back();
        }
    }

#ifdef DEBUG
    void helper() {
        std::cout << "\t\tcache: ";
        for (const auto &c : mCacheList)
            std::cout << "(" << c.first << ", " << c.second << "), ";
        std::cout << std::endl;
    }
#endif // DEBUG
private:
    list<pair<int /* key */, int /* value */>> mCacheList;
    unordered_map<int /* key */, decltype(mCacheList)::iterator /* pos */> mCacheMap;
    int mCapacity;
};

#define PUT(k, v) {                                         \
    std::cout << "put (" << k << ", " << v << ")\n";        \
    cache.put(k, v);                                        \
    cache.helper();                                         \
}

#define GET(k) {                                            \
    auto v = cache.get(k);                                  \
    std::cout << "get (" << k << ") is (" << v << ")\n";    \
    cache.helper();                                         \
}

int main() {
    LRUCache cache{2}; // set capacity
    //cache.put(1, 1);
    PUT(1, 1);
    //cache.put(2, 2);
    PUT(2, 2);
    //cache.get(1);       // returns 1
    GET(1);
    //cache.put(3, 3);    // evicts key 2
    PUT(3, 3);
    //cache.get(2);       // returns -1 (not found)
    GET(2);
    //cache.put(4, 4);    // evicts key 1
    PUT(4, 4);
    //cache.get(1);       // returns -1 (not found)
    GET(1);
    //cache.get(3);       // returns 3
    GET(3);
    //cache.get(4);       // returns 4
    GET(4);
}