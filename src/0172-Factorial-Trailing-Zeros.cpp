/**
 * Given an integer n, return the number of trailing zeroes in n!.
 * Example 1:
 * Input: 3
 * Output: 0
 * Explanation: 3! = 6, no trailing zero.
 *
 * Example 2:
 * Input: 5
 * Output: 1
 * Explanation: 5! = 120, one trailing zero.
 * Note: Your solution should be in logarithmic time complexity.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    int trailingZeroes(int n) {
        int zeros = 0;
        while (n != 0) {
            zeros += n / 5;
            n /= 5;
        }
        return zeros;
    }
};

int main() {
    Solution sln;
    std::vector<int> ns{3, 5, 20, 30};

    for (auto &n : ns) {
        TestCount();
        std::cout << sln.trailingZeroes(n) << std::endl;
    }
}