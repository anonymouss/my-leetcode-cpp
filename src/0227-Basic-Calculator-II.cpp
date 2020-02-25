/**
 * Implement a basic calculator to evaluate a simple expression string.
 * The expression string contains only non-negative integers, +, -, *, / operators and empty spaces.
 * The integer division should truncate toward zero.
 *
 * Example 1:
 * Input: "3+2*2"
 * Output: 7
 *
 * Example 2:
 * Input: " 3/2 "
 * Output: 1
 *
 * Example 3:
 * Input: " 3+5 / 2 "
 * Output: 5
 *
 * Note:
 * You may assume that the given expression is always valid.
 * Do not use the eval built-in library function.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stack>

class Solution {
public:
    int calculate(std::string s) {
        long number = 0, operand1 = 0, operand2 = 0;
        for (auto i = 0; i < s.length(); ++i) {
            if (std::isdigit(s[i])) {
                while (std::isdigit(s[i])) {
                    number = number * 10 + s[i] - '0';
                    ++i;
                }
                --i;
                operands.emplace(number);
                number = 0;
                if (!operators.empty() && isPrecedency(operators.top())) {
                    auto op1 = operands.top();
                    operands.pop();
                    auto op2 = operands.top();
                    operands.pop();
                    auto opt = operators.top();
                    operators.pop();
                    operands.emplace((opt == '*') ? (op2 * op1) : op2 / op1);
                }
            } else if (isoperator(s[i])) {
                if (!operators.empty() && !isPrecedency(s[i])) {
                    auto op1 = operands.top();
                    operands.pop();
                    auto op2 = operands.top();
                    operands.pop();
                    auto opt = operators.top();
                    operators.pop();
                    operands.emplace((opt == '+') ? (op1 + op2) : op2 - op1);
                }
                operators.emplace(s[i]);
            }
        }
        while (!operators.empty()) {
            auto op1 = operands.top();
            operands.pop();
            auto op2 = operands.top();
            operands.pop();
            auto opt = operators.top();
            operators.pop();
            operands.emplace((opt == '+') ? (op2 + op1) : op2 - op1);
        }
        return static_cast<int>(operands.top());
    }

private:
    std::stack<long> operands;
    std::stack<char> operators;

    bool isPrecedency(const char &opt) {
        return opt == '*' || opt == '/';
    }

    bool isoperator(const char &opt) {
        return opt == '+' || opt == '-' || opt == '*' || opt == '/';
    }
};

int main() {
    Solution sln;

    std::vector<std::string> ss{"3+2*2", " 3/2 ", " 3+5 / 2 ", "1-1+1"};

    for (auto &s : ss) {
        TestCount();
        std::cout << sln.calculate(s) << std::endl;
    }
}