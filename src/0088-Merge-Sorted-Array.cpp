/**
 * Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
 * Note:
 * - The number of elements initialized in nums1 and nums2 are m and n respectively.
 * - You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold
 *   additional elements from nums2.
 *
 * Example:
 * Input:
 * nums1 = [1,2,3,0,0,0], m = 3
 * nums2 = [2,5,6],       n = 3
 * Output: [1,2,2,3,5,6]
 */

#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int end1 = m - 1, end2 = n - 1, pos = nums1.size() - 1;
        while(pos >= 0) {
            if (end1 >= 0 && (end2 < 0 || nums1[end1] > nums2[end2])) {
                nums1[pos--] = nums1[end1--];
            } else {
                nums1[pos--] = nums2[end2--];
            }
        }
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<pair<vector<int>, int>>> inputs{
        {
            // 1
            {
                {1, 2, 3, 0, 0, 0}, // nums1
                3                   // m
            },
            // 2
            {
                {2, 5, 6},          // nums2
                3                   // n
            }
        },
        {
            {
                {1},
                1
            },
            {
                {},
                0
            }
        },
        {
            {
                {0, 0, 3, 0, 0, 0, 0, 0, 0},
                3
            },
            {
                {-1, 1, 1, 1, 2, 3},
                6
            }
        }
    };

    for (auto &input : inputs) {
        s.merge(input[0].first, input[0].second, input[1].first, input[1].second);
        std::cout << "Case " << testId++ << ": ";
        for (const auto &e : input[0].first) std::cout << e << ", ";
        std::cout << std::endl;
    }
}