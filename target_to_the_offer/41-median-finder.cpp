/* 如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

例如，
[2,3,4] 的中位数是 3
[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：
void addNum(int num) - 从数据流中添加一个整数到数据结构中。
double findMedian() - 返回目前所有元素的中位数。

示例 1：
输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]

示例 2：
输入：
["MedianFinder","addNum","findMedian","addNum","findMedian"]
[[],[2],[],[3],[]]
输出：[null,null,2.00000,null,2.50000]

限制：
最多会对 addNum、findMedian 进行 50000 次调用。
注意：本题与主站 295 题相同：https://leetcode-cn.com/problems/find-median-from-data-stream/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <functional>

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {}
    
    void addNum(int num) {
        ascendQueue.emplace(num);
        descendQueue.emplace(ascendQueue.top());
        ascendQueue.pop();

        if (ascendQueue.size() < descendQueue.size()) {
            ascendQueue.emplace(descendQueue.top());
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
    std::priority_queue<int, std::vector<int>, std::greater<int>> ascendQueue; // 最小堆
    std::priority_queue<int, std::vector<int>, std::less<int>> descendQueue; // 最大堆
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