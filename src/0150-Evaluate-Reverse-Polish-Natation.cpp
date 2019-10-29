/**
 * Evaluate the value of an arithmetic expression in Reverse Polish Notation.
 * Valid operators are +, -, *, /. Each operand may be an integer or another expression.
 * Note:
 * Division between two integers should truncate toward zero.
 * The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.
 * Example 1:
 * Input: ["2", "1", "+", "3", "*"]
 * Output: 9
 * Explanation: ((2 + 1) * 3) = 9
 * Example 2:
 * Input: ["4", "13", "5", "/", "+"]
 * Output: 6
 * Explanation: (4 + (13 / 5)) = 6
 * Example 3:
 * Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
 * Output: 22
 * Explanation: 
 *   ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
 * = ((10 * (6 / (12 * -11))) + 17) + 5
 * = ((10 * (6 / -132)) + 17) + 5
 * = ((10 * 0) + 17) + 5
 * = (0 + 17) + 5
 * = 17 + 5
 * = 22
 */

#include "MyMisc.h"

#include <vector>
#include <string>
#include <stack>

class Solution {
public:
    int evalRPN(std::vector<std::string>& tokens) {
        std::stack<int> tokensStack;
        for (const auto &token : tokens) {
            if (token == "+") {
                auto op = tokensStack.top();
                tokensStack.pop();
                tokensStack.top() += op;
            } else if (token == "-") {
                auto op = tokensStack.top();
                tokensStack.pop();
                tokensStack.top() -= op;
            } else if (token == "*") {
                auto op = tokensStack.top();
                tokensStack.pop();
                tokensStack.top() *= op;
            } else if (token == "/") {
                auto op = tokensStack.top();
                tokensStack.pop();
                tokensStack.top() /= op;
            } else {
                tokensStack.emplace(std::stoi(token));
            }
        }
        return tokensStack.top();
    }
};

int main() {
    Solution s;
    
    std::vector<std::vector<std::string>> input_tokens {
        {"2", "1", "+", "3", "*"},
        {"4", "13", "5", "/", "+"},
        {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}
    };

    for (auto &tokens : input_tokens) {
        TestCount();
        std::cout << s.evalRPN(tokens) << std::endl;
    }
}