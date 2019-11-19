/**
 * Given an unsorted array, find the maximum difference between the successive elements in its
 * sorted form.
 * Return 0 if the array contains less than 2 elements.
 *
 * Example 1:
 * Input: [3,6,9,1]
 * Output: 3
 * Explanation: The sorted form of the array is [1,3,6,9], either
 *              (3,6) or (6,9) has the maximum difference 3.
 *
 * Example 2:
 * Input: [10]
 * Output: 0
 * Explanation: The array contains less than 2 elements, therefore return 0.
 *
 * Note:
 * You may assume all elements in the array are non-negative integers and fit in the 32-bit signed
 * integer range.
 * Try to solve it in linear time/space.
 */

#include "MyMisc.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#define COMPILE_VERSION 2

#if COMPILE_VERSION == 1
class Solution {
public:
    int maximumGap(std::vector<int> &nums) {
        if (nums.empty() || nums.size() < 2) return 0;
        int maxVal = *std::max_element(nums.begin(), nums.end());
        int exp = 1;
        int radix = 10;
        std::vector<int> aux(nums.size());

        while (maxVal / exp > 0) {
            std::vector<int> count(radix, 0);
            for (int i = 0; i < nums.size(); i++) count[(nums[i] / exp) % 10]++;
            for (int i = 1; i < count.size(); i++) count[i] += count[i - 1];
            // https://segmentfault.com/q/1010000006110201
            for (int i = nums.size() - 1; i >= 0; i--) aux[--count[(nums[i] / exp) % 10]] = nums[i];
            for (int i = 0; i < nums.size(); i++) nums[i] = aux[i];
            exp *= 10;
        }
        int maxGap = 0;
        for (int i = 0; i < nums.size() - 1; i++) maxGap = std::max(nums[i + 1] - nums[i], maxGap);
        return maxGap;
    }
};
#elif COMPILE_VERSION == 2
class Solution {
public:
    struct Bucket {
        bool used = false;
        int minval = std::numeric_limits<int>::max();
        int maxval = std::numeric_limits<int>::min();
    };

    int maximumGap(std::vector<int> &nums) {
        if (nums.empty() || nums.size() < 2) return 0;
        auto mini = *std::min_element(nums.begin(), nums.end());
        auto maxi = *std::max_element(nums.begin(), nums.end());
        auto bucketSize = std::max(1, (maxi - mini) / ((int)nums.size() - 1));
        auto bucketNum = (maxi - mini) / bucketSize + 1;
        std::vector<Bucket> buckets(bucketNum);

        for (auto &e : nums) {
            auto bucketIndex = (e - mini) / bucketSize;
            buckets[bucketIndex].used = true;
            buckets[bucketIndex].minval = std::min(e, buckets[bucketIndex].minval);
            buckets[bucketIndex].maxval = std::max(e, buckets[bucketIndex].maxval);
        }

        auto prevBucketMax = mini, maxGap = 0;
        for (auto &bucket : buckets) {
            if (!bucket.used) continue;
            maxGap = std::max(maxGap, bucket.minval - prevBucketMax);
            prevBucketMax = bucket.maxval;
        }
        return maxGap;
    }
};
#endif

int main() {
    Solution sln;
    std::vector<std::vector<int>> inputs{{3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48},
                                         {1, 3, 4, 6, 7, 9, 10, 12}};

    for (auto &nums : inputs) {
        TestCount();
        std::cout << sln.maximumGap(nums) << std::endl;
    }
}