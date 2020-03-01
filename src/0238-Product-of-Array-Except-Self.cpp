/**
 * Given an array nums of n integers where n > 1,  return an array output such that output[i] is
 * equal to the product of all the elements of nums except nums[i].
 *
 * Example:
 * Input:  [1,2,3,4]
 * Output: [24,12,8,6]
 * Note: Please solve it without division and in O(n).
 *
 * Follow up:
 * Could you solve it with constant space complexity? (The output array does not count as extra
 * space for the purpose of space complexity analysis.)
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> productExceptSelf(std::vector<int> &nums) {
        int size = nums.size();
        std::vector<int> leftProducts(size, 1);
        std::vector<int> rightProducts(size, 1);
        for (auto l = 1; l < size; ++l) {
            leftProducts[l] = leftProducts[l - 1] * nums[l - 1];
        }
        for (auto r = size - 2; r >= 0; --r) {
            rightProducts[r] = rightProducts[r + 1] * nums[r + 1];
        }
        std::vector<int> resultProducts(size);
        for (auto i = 0; i < size; ++i) {
            resultProducts[i] = leftProducts[i] * rightProducts[i];
        }
        return resultProducts;
    }
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> inputs{
        {1, 2, 3, 4},
    };

    auto print_v = [](const std::vector<int> &products) {
        std::cout << "[";
        for (const auto &p : products) {
            std::cout << p << ", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &nums : inputs) {
        TestCount();
        print_v(sln.productExceptSelf(nums));
    }
}