/**
 * Count the number of prime numbers less than a non-negative number, n.
 *
 * Example:
 * Input: 10
 * Output: 4
 * Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    int countPrimes(int n) {
        if (n == 0 || n == 1) return 0;
        std::vector<int> primes(n, 1);
        auto count = 0;
        for (auto i = 2; i < n; ++i) {
            if (primes[i] == 1) {
                ++count;
                for (auto j = i + i; j < n; j += i) {
                    primes[j] = 0;
                }
            }
        }
        return count;
    }
};

int main() {
    Solution sln;
    std::vector<int> nv{10};

    for (auto &n : nv) {
        TestCount();
        std::cout << sln.countPrimes(n) << std::endl;
    }
}