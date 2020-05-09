/**
 * Median is the middle value in an ordered integer list. If the size of the list is even, there is
 * no middle value. So the median is the mean of the two middle value.
 *
 * For example,
 * [2,3,4], the median is 3
 * [2,3], the median is (2 + 3) / 2 = 2.5
 * Design a data structure that supports the following two operations:
 * void addNum(int num) - Add a integer number from the data stream to the data structure.
 * double findMedian() - Return the median of all elements so far.
 *
 * Example:
 * addNum(1)
 * addNum(2)
 * findMedian() -> 1.5
 * addNum(3)
 * findMedian() -> 2
 *
 * Follow up:
 * If all integer numbers from the stream are between 0 and 100, how would you optimize it?
 * If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {}

    void addNum(int num) {
        ascendQueue.push(num);
        descendQueue.push(ascendQueue.top());
        ascendQueue.pop();

        if (ascendQueue.size() < descendQueue.size()) {
            ascendQueue.push(descendQueue.top());
            descendQueue.pop();
        }
    }

    double findMedian() {
        if (ascendQueue.size() > descendQueue.size()) {
            return static_cast<double>(ascendQueue.top());
        } else {
            return (ascendQueue.top() + descendQueue.top()) * 0.5;
        }
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> ascendQueue;
    std::priority_queue<int, std::vector<int>, std::less<int>> descendQueue;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main() {
    MedianFinder finder;
    finder.addNum(1);
    finder.addNum(2);
    std::cout << finder.findMedian() << std::endl;
    finder.addNum(3);
    std::cout << finder.findMedian() << std::endl;
}