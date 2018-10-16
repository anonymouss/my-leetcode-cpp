/**
 * Given two integers dividend and divisor, divide two integers without using
 * multiplication, division and mod operator.
 * Return the quotient after dividing dividend by divisor.
 * The integer division should truncate toward zero.
 *
 * Example 1:
 * Input: dividend = 10, divisor = 3
 * Output: 3
 *
 * Example 2:
 * Input: dividend = 7, divisor = -3
 * Output: -2
 *
 * Note:
 * Both dividend and divisor will be 32-bit signed integers.
 * The divisor will never be 0.
 * Assume we are dealing with an environment which could only store integers
 * within the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose
 * of this problem, assume that your function returns 2^31 − 1 when the division
 * result overflows.
 */

#include <iostream>

class Solution {
public:
    int divide(int dividend, int divisor) {
        bool isSame = (dividend < 0 && divisor < 0)
                        || (dividend >= 0 && divisor >= 0);
        int64_t newDividend = ABS(dividend), newDivisor = ABS(divisor);

        int64_t res = doDivide(newDividend, newDivisor);
        return clip(isSame ? res : -res);
    }

    int64_t doDivide(int64_t dividend, int64_t divisor) {
        if (dividend < divisor) return 0;
        int64_t count = 1, sum = divisor;
        while ((sum + sum) < dividend) {
            count += count;
            sum += sum;
        }
        return count + doDivide(dividend - sum, divisor);
    }

    inline int clip(int64_t val) {
        if (val < INT32_MIN) return INT32_MIN;
        if (val > INT32_MAX) return INT32_MAX;
        return static_cast<int>(val);
    }

    inline int64_t ABS(int val) {
        int64_t v = static_cast<int64_t>(val);
        return v < 0 ? -v : v;
    }
};


int main() {
    Solution s;

    int dividend1 = 10, divisor1 = 3;
    int dividend2 = 7, divisor2 = -3;
    int dividend3 = -2147483648, divisor3 = 2;
    int dividend4 = -2147483648, divisor4 = -1;

    std::cout << "Case 1: " << s.divide(dividend1, divisor1) << std::endl;
    std::cout << "Case 2: " << s.divide(dividend2, divisor2) << std::endl;
    std::cout << "Case 3: " << s.divide(dividend3, divisor3) << std::endl;
    std::cout << "Case 4: " << s.divide(dividend3, divisor4) << std::endl;
}