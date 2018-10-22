/**
 * Implement pow(x, n), which calculates x raised to the power n (x^n).
 *
 * Example 1:
 * Input: 2.00000, 10
 * Output: 1024.00000
 *
 * Example 2:
 * Input: 2.10000, 3
 * Output: 9.26100
 *
 * Example 3:
 * Input: 2.00000, -2
 * Output: 0.25000
 * Explanation: 2^-2 = 1/2^2 = 1/4 = 0.25
 *
 * Note:
 * -100.0 < x < 100.0
 * n is a 32-bit signed integer, within the range [−2^31, 2^31 − 1]
 */

#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

class Solution {
public:
    // x^2 = x^(n/2) * x^(n/2) * x^(n%2)
    double myPow(double x, int n) {
        if (n < 0)
            return 1.0 / pow(x, -n);
        else
            return pow(x, n);
    }

    double pow(double x, int n) {
        if (n == 0) return 1.0;

        auto v = pow(x, n / 2);

        if (n % 2 == 0)
            return v * v;
        else
            return v * v * x; 
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<double> xs{2.0, 2.1, 2.0};
    vector<int> ns{10, 3, -2};

    if (xs.size() != ns.size()) {
        std::cout << "incorrect test cases\n";
        return -1;
    }

    for (int i = 0; i < xs.size(); ++i) {
        auto res = s.myPow(xs[i], ns[i]);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}