/**
 * Given a 32-bit signed integer, reverse digits of an integer.
 *
 * Example 1:
 * Input: 123
 * Output: 321
 * 
 * Example 2:
 * Input: -123
 * Output: -321
 * 
 * Example 3:
 * Input: 120
 * Output: 21
 * Note: Assume we are dealing with an environment which could only store
 * integers within the 32-bit signed integer, range: [−2^31,  2^31 − 1]. For the
 * purpose of this problem, assume that your function returns 0 when the
 * reversed integer overflows.
 */

#include <iostream>

class Solution {
public:
    int reverse(int x) {
        int flag = x < 0 ? -1 : 1;
        int64_t xx = x * flag;
        int64_t res = 0;
        while (xx > 0) {
            auto i = xx % 10;
            xx /= 10;
            res = res * 10 + i;
        }
        res *= flag;
        if (res > INT32_MAX || res < INT32_MIN) return 0;
        return static_cast<int>(res);
    }
};

int main() {
    Solution s;

    int x1 = 123;
    int x2 = -123;
    int x3 = 120;
    int x4 = INT32_MAX;
    int x5 = INT32_MIN;

    std::cout << "Case 1: " << s.reverse(x1) << std::endl;
    std::cout << "Case 2: " << s.reverse(x2) << std::endl;
    std::cout << "Case 3: " << s.reverse(x3) << std::endl;
    std::cout << "Case 4: " << s.reverse(x4) << std::endl;
    std::cout << "Case 5: " << s.reverse(x5) << std::endl;
}