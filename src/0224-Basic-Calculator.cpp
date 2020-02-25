/**
 * Implement a basic calculator to evaluate a simple expression string.
 * The expression string may contain open ( and closing parentheses ), the plus + or minus sign -,
 * non-negative integers and empty spaces .
 *
 * Example 1:
 * Input: "1 + 1"
 * Output: 2
 *
 * Example 2:
 * Input: " 2-1 + 2 "
 * Output: 3
 *
 * Example 3:
 * Input: "(1+(4+5+2)-3)+(6+8)"
 * Output: 23
 *
 * Note:
 * You may assume that the given expression is always valid.
 * Do not use the eval built-in library function.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cctype>

class Solution {
public:
    int calculate(std::string s) {
        long result = 0,operand = 0, sign = 1;
        std::stack<int> opStack;
        for (auto &c : s) {
            if (std::isdigit(c)) {
                operand = operand * 10 + c - '0';
            } else if (c == '+') {
                result += sign * operand;
                sign = 1;
                operand = 0;
            } else if (c == '-') {
                result += sign * operand;
                sign = -1;
                operand = 0;
            } else if (c == '(') {
                opStack.emplace(result);
                opStack.emplace(sign);
                result = 0;
                sign = 1;
            } else if (c == ')') {
                result += sign * operand;
                result *= opStack.top(); // sign
                opStack.pop();
                result += opStack.top(); // operand
                opStack.pop();
                operand = 0;
            }
        }
        return static_cast<int>(result + sign * operand);
    }
};

int main() {
    Solution sln;

    std::vector<std::string> ss{"1 + 1", "2-1 + 2", "(1+(4+5+2)-3)+(6+8)", "2147483647"};

    for (auto &s : ss) {
        TestCount();
        std::cout << sln.calculate(s) << std::endl;
    }
}