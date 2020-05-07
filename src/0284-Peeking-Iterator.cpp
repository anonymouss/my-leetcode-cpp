/**
 * Given an Iterator class interface with methods: next() and hasNext(), design and implement a
 * PeekingIterator that support the peek() operation -- it essentially peek() at the element that
 * will be returned by the next call to next().
 *
 * Example:
 *
 * Assume that the iterator is initialized to the beginning of the list: [1,2,3].
 * Call next() gets you 1, the first element in the list.
 * Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.
 * You call next() the final time and it returns 3, the last element.
 * Calling hasNext() after that should return false.
 *
 * Follow up:
 * How would you extend your design to be generic and work with all types, not just integer?
 */

#include "MyMisc.h"

#include <iostream>
#include <queue>
#include <vector>

// simple Iterator impl
class Iterator {
public:
    Iterator(const std::vector<int> &nums) {
        for (const auto &n : nums) { mData.emplace(n); }
    }

    // Returns the next element in the iteration.
    int next() {
        if (!hasNext()) return -1;
        auto n = mData.front();
        mData.pop();
        return n;
    }

    // Returns true if the iteration has more elements.
    bool hasNext() const { return !mData.empty(); }

private:
    std::queue<int> mData;
};

class PeekingIterator : public Iterator {
public:
    PeekingIterator(const std::vector<int> &nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        _peek_cache = -1;
        _has_cache = false;
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        if (!hasNext()) return -1;
        if (!_has_cache) {
            _peek_cache = next();
            _has_cache = true;
        }
        return _peek_cache;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        if (_has_cache) {
            _has_cache = false;
            return _peek_cache;
        }
        return Iterator::next();
    }

    bool hasNext() const { return _has_cache || Iterator::hasNext(); }

private:
    int _peek_cache;
    bool _has_cache;
};

int main() {
    TestCount(IOFormat::BOOL);
    PeekingIterator pitr{{1, 2, 3}};
    std::cout << pitr.next() << std::endl;
    std::cout << pitr.peek() << std::endl;
    std::cout << pitr.next() << std::endl;
    std::cout << pitr.next() << std::endl;
    std::cout << pitr.hasNext() << std::endl;
}