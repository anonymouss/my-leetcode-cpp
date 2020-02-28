/**
 * Given an integer n, count the total number of digit 1 appearing in all non-negative integers less
 * than or equal to n.
 *
 * Example:
 * Input: 13
 * Output: 6 
 * 
 * Explanation: Digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int countDigitOne(int n) {
        auto countr = 0;
        for (long long i = 1; i <= n; i *= 10) {
            long long divider = i * 10;
            countr += (n / divider) * i + std::min(std::max(n % divider - i + 1, 0LL), i);
        }
        return countr;
    }
};

int main() {
    Solution sln;

    std::vector<int> ns{13};

    for (auto &n : ns) {
        TestCount();
        std::cout << sln.countDigitOne(n) << std::endl;
    }
}