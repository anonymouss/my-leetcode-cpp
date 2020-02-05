/**
 * Given a column title as appear in an Excel sheet, return its corresponding column number.
 * For example:
 *     A -> 1
 *     B -> 2
 *     C -> 3
 *     ...
 *     Z -> 26
 *     AA -> 27
 *     AB -> 28
 *     ...
 *
 * Example 1:
 * Input: "A"
 * Output: 1
 *
 * Example 2:
 * Input: "AB"
 * Output: 28
 *
 * Example 3:
 * Input: "ZY"
 * Output: 701
 */

#include "MyMisc.h"

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int titleToNumber(std::string s) {
        long number = 0;
        long base = 1;
        for (int i = s.length() - 1; i >= 0; --i) {
            int dec = s[i] - 'A' + 1;
            number += dec * base;
            base *= 26;
        }
        return number;
    }
};

int main() {
    Solution sln;
    std::vector<std::string> ss{"A", "AB", "ZY", "CFDGSXM"};

    for (auto &s : ss) {
        TestCount();
        std::cout << sln.titleToNumber(s) << std::endl;
    }
}