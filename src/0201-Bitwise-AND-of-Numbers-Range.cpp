/**
 * Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in
 * this range, inclusive.
 *
 * Example 1:
 * Input: [5,7]
 * Output: 4
 *
 * Example 2:
 * Input: [0,1]
 * Output: 0
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <utility>

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        while (n > m) {
            n &= (n - 1);
        }
        return n;
    }
};

int main() {
    Solution sln;

    std::vector<std::pair<int, int>> mnv{
        {5, 7}, {0, 1}
    };

    for (const auto &mn : mnv) {
        TestCount();
        std::cout << sln.rangeBitwiseAnd(mn.first, mn.second) << std::endl;
    }
}