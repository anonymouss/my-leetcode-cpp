/**
 * Find the kth largest element in an unsorted array. Note that it is the kth largest element in the
 * sorted order, not the kth distinct element.
 *
 * Example 1:
 * Input: [3,2,1,5,6,4] and k = 2
 * Output: 5
 *
 * Example 2:
 * Input: [3,2,3,1,2,4,5,5,6] and k = 4
 * Output: 4
 *
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ array's length.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class Solution {
public:
    int findKthLargest(std::vector<int> &nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        for (auto &n : nums) {
            pq.emplace(n);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }
};

struct Input {
    std::vector<int> nums;
    int k;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{
        {{3, 2, 1, 5, 6, 4}, 2},
        {{3, 2, 3, 1, 2, 4, 5, 5, 6}, 4}
    };

    for (auto &input : inputs) {
        TestCount();
        std::cout << sln.findKthLargest(input.nums, input.k) << std::endl;
    }
}