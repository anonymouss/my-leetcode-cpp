/**
 * Write an algorithm to determine if a number is "happy".
 * A happy number is a number defined by the following process: Starting with any positive integer,
 * replace the number by the sum of the squares of its digits, and repeat the process until the
 * number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
 * Those numbers for which this process ends in 1 are happy numbers.
 *
 * Example: 
 * Input: 19
 * Output: true
 * Explanation: 
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    bool isHappy(int n) {
        auto slow = n, fast = n;
        do {
            slow = expand(slow);
            fast = expand(fast);
            fast = expand(fast);
        } while(slow != fast);
        return slow == 1;
    }

private:
    int expand(int n) {
        auto sum = 0;
        while (n > 0) {
            auto highest = n % 10;
            sum += highest * highest;
            n /= 10;
        }
        return sum;
    }
};

int main() {
    Solution sln;
    std::vector<int> nv{19};

    for (auto &n : nv) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.isHappy(n) << std::endl;
    }
}