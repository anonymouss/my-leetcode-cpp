/**
 * Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive),
 * prove that at least one duplicate number must exist. Assume that there is only one duplicate
 * number, find the duplicate one.
 *
 * Example 1:
 * Input: [1,3,4,2,2]
 * Output: 2
 *
 * Example 2:
 * Input: [3,1,3,4,2]
 * Output: 3
 *
 * Note:
 * You must not modify the array (assume the array is read only).
 * You must use only constant, O(1) extra space.
 * Your runtime complexity should be less than O(n2).
 * There is only one duplicate number in the array, but it could be repeated more than once.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

#define SIMPLE_METHOD 0
#define PASS_METHOD 1

#define COMPILE_VERSION PASS_METHOD

#if (COMPILE_VERSION == SIMPLE_METHOD)
// simplest method but TLE
class Solution {
public:
    int findDuplicate(std::vector<int> &nums) {
        auto duplicate = nums[0];
        for (auto start = 0; start < nums.size() - 1; ++start) {
            for (auto i = start + 1; i < nums.size(); ++i) {
                if (nums[i] == nums[start]) { return nums[i]; }
            }
        }
        // SHOULD NEVER COME INTO HERE
        return -1;
    }
};
#elif (COMPILE_VERSION == PASS_METHOD)
class Solution {
public:
    int findDuplicate(std::vector<int> &nums) {
        // Find the intersection point of the two runners.
        int tortoise = nums[0];
        int hare = nums[0];
        do {
            tortoise = nums[tortoise];
            hare = nums[nums[hare]];
        } while (tortoise != hare);

        // Find the "entrance" to the cycle.
        int ptr1 = nums[0];
        int ptr2 = tortoise;
        while (ptr1 != ptr2) {
            ptr1 = nums[ptr1];
            ptr2 = nums[ptr2];
        }

        return ptr1;
    }
};
#endif

int main() {
    Solution sln;
    std::vector<std::vector<int>> inputs{{1, 3, 4, 2, 2}, {3, 1, 3, 4, 2}};

    for (auto &nums : inputs) {
        TestCount();
        std::cout << sln.findDuplicate(nums) << std::endl;
    }
}