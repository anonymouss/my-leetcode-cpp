/**
 * Given an array nums of n integers and an integer target, find three integers in nums
 * such that the sum is closest to target. Return the sum of the three integers. You may
 * assume that each input would have exactly one solution.
 *
 * Example:
 * Given array nums = [-1, 2, 1, -4], and target = 1.
 * The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

#define ABS(val) ((val < 0) ? -(val) : val)

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int closestSum = 0, closestDistance = INT32_MAX, size = nums.size();
        for (int i = 0; i < size - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int a = nums[i], l = i + 1, r = size - 1;
            auto skipLeft = [&]() { while (l < size && nums[l] == nums[l + 1]) ++l; };
            auto skipRight = [&]() { while (r > i && nums[r] == nums[r - 1]) --r; };
            while (l < r) {
                int b = nums[l], c = nums[r];
                int sum = a + b + c;
                if (sum == target) {
                    return sum;
                } else if (sum > target) {
                    skipRight();
                    --r;
                } else {
                    skipLeft();
                    ++l;
                }
                int distance = ABS(sum - target);
                if (distance < closestDistance) {
                    closestDistance = distance;
                    closestSum = sum;
                }
            }
        }
        return closestSum;
    }
};

int main() {
    Solution s;

    vector<int> nums1{-1, 2, 1, -4}; int target1 = 1;

    std::cout << "Case 1: " << s.threeSumClosest(nums1, target1) << std::endl;
}