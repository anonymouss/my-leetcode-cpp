/**
 * Implement int sqrt(int x).
 * Compute and return the square root of x, where x is guaranteed to be a non-negative integer.
 * Since the return type is an integer, the decimal digits are truncated and only the integer part
 * of the result is returned.
 *
 * Example 1:
 * Input: 4
 * Output: 2
 *
 * Example 2:
 * Input: 8
 * Output: 2
 * Explanation: The square root of 8 is 2.82842..., and since 
 *              the decimal part is truncated, 2 is returned.
 */

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERISON 2

#if (COMPILE_VERISON == 0)
class Solution {
public:
    int mySqrt(int x) {
        int half = x / 2 + 1;
        int i = 1;
        for (; i <= half && (x/i >= i); ++i);
        return i - 1;
    }
};
#elif (COMPILE_VERISON == 1)
// binary
class Solution {
public:
    int mySqrt(int x) {
        if (x <= 1) return x;
        int l = 0, r = x;
        while (l < r) {
            auto m = l + (r - l) / 2;
            if (x / m >= m) l = m + 1;
            else r = m;
        }
        return r - 1;
    }
};
#elif (COMPILE_VERISON == 2)
// newton
class Solution {
public:
    int mySqrt(int x) {
        long res = x;
        while (res * res > x) {
            res = (res + x / res) / 2;
        }
        return res;
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<int> xs{1, 4, 8, 2147395600};

    std::cout << INT32_MAX << std::endl;
    for (auto &x : xs) {
        auto r = s.mySqrt(x);
        std::cout << "Case " << testId++ << ": " << r << std::endl;
    }
}