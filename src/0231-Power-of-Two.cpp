/**
 * Given an integer, write a function to determine if it is a power of two.
 *
 * Example 1:
 * Input: 1
 * Output: true 
 * Explanation: 2^0 = 1
 *
 * Example 2:
 * Input: 16
 * Output: true
 * Explanation: 2^4 = 16
 *
 * Example 3:
 * Input: 218
 * Output: false
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    bool isPowerOfTwo(int n) {
        // not cover < 0 cases, like 2^0.5 
        if (n < 1) return false;
        if (n == 1) {
            return true;
        }
        if (n % 2 != 0) {
            return false;
        }
        return isPowerOfTwo(n / 2);
    }
};

int main() {
    Solution sln;

    std::vector<int> ns{1, 16, 218, 0};

    for (auto &n : ns) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.isPowerOfTwo(n) << std::endl;
    }
}