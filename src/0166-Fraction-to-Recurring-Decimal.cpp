/**
 * Given two integers representing the numerator and denominator of a fraction, return the fraction
 * in string format.
 * If the fractional part is repeating, enclose the repeating part in parentheses.
 *
 * Example 1:
 * Input: numerator = 1, denominator = 2
 * Output: "0.5"
 *
 * Example 2:
 * Input: numerator = 2, denominator = 1
 * Output: "2"
 *
 * Example 3:
 * Input: numerator = 2, denominator = 3
 * Output: "0.(6)"
 */

#include "MyMisc.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::string fractionToDecimal(int numerator, int denominator) {
        if (denominator == 0) return "";
        if (numerator == 0) return "0";
        std::string result = "";
        bool negflag = false;
        int64_t num = numerator, denom = denominator;
        if (denom < 0) {
            negflag = !negflag;
            denom = -denom;
        }
        if (num < 0) {
            negflag = !negflag;
            num = -num;
        }
        if (negflag) result.append("-");
        result.append(std::to_string(num / denom));
        num %= denom;
        if (num == 0) return result;
        result.append(".");
        int index = result.length() - 1;
        std::unordered_map<int, int> buckets;
        while (num && buckets.count(num) == 0) {
            buckets[num] = ++index;
            num *= 10;
            result.append(std::to_string(num / denom));
            num %= denom;
        }
        if (buckets.count(num) > 0) {
            result.insert(buckets[num], "(");
            result.append(")");
        }
        return result;
    }
};

int main() {
    Solution sln;
    std::vector<int> numerators{1, 2, 2, 4};
    std::vector<int> denominators{2, 1, 3, 333};

    for (auto i = 0; i < numerators.size(); ++i) {
        TestCount();
        std::cout << sln.fractionToDecimal(numerators[i], denominators[i]) << std::endl;
    }
}