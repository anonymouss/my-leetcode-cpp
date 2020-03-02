/**
 * Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.
 *
 * Example:
 * Input: 38
 * Output: 2 
 * Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2. 
 *              Since 2 has only one digit, return it.
 *
 * Follow up:
 * Could you do it without any loop/recursion in O(1) runtime?
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    int addDigits(int num) {
        if (num / 10 == 0) {
            return num;
        }
        int result = 0;
        while (num) {
            result += num % 10;
            num /= 10;
        }
        return addDigits(result);
    }
};

int main() {
    Solution sln;

    std::vector<int> nums{38};

    for (auto &num : nums) {
        TestCount();
        std::cout << sln.addDigits(num) << std::endl;
    }
}