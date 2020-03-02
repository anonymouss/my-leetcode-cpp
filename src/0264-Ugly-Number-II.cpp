/**
 * Write a program to find the n-th ugly number.
 * Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
 *
 * Example:
 * Input: n = 10
 * Output: 12
 * Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
 *
 * Note:  
 * 1 is typically treated as an ugly number.
 * n does not exceed 1690.。
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int nthUglyNumber(int n) {
        return generator.getUglyNumber(n);
    }

private:
    class UglyNumberGenerator {
    public:
        UglyNumberGenerator() {
            uglyNumbers[0] = 1;
            size = 1;
            i2 = 0;
            i3 = 0;
            i5 = 0;
        }

        int getUglyNumber(int index) {
            if (index > MAX_CAPACITY) return -1;
            if (index > size) {
                for (auto i = size; i < index; ++i) {
                    auto ugly = std::min(std::min(uglyNumbers[i2] * 2, uglyNumbers[i3] * 3),
                            uglyNumbers[i5] * 5);
                    uglyNumbers[i] = ugly;
                    if (ugly == uglyNumbers[i2] * 2) ++i2;
                    if (ugly == uglyNumbers[i3] * 3) ++i3;
                    if (ugly == uglyNumbers[i5] * 5) ++i5;
                }
            }
            size = index;
            return uglyNumbers[index - 1];
        }
    
    private:
        static constexpr int MAX_CAPACITY = 1690;
        int uglyNumbers[MAX_CAPACITY];
        int size;
        int i2, i3, i5;
    };

    UglyNumberGenerator generator;
};

int main() {
    Solution sln;

    std::vector<int> ns{10};

    for (auto &n : ns) {
        TestCount();
        std::cout << sln.nthUglyNumber(n) << std::endl;
    }
}