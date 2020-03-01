/**
 * Given a string of numbers and operators, return all possible results from computing all the
 * different possible ways to group numbers and operators. The valid operators are +, - and *.
 *
 * Example 1:
 * Input: "2-1-1"
 * Output: [0, 2]
 * Explanation: 
 * ((2-1)-1) = 0 
 * (2-(1-1)) = 2
 *
 * Example 2:
 * Input: "2*3-4*5"
 * Output: [-34, -14, -10, -10, 10]
 * Explanation: 
 * (2*(3-(4*5))) = -34 
 * ((2*3)-(4*5)) = -14 
 * ((2*(3-4))*5) = -10 
 * (2*((3-4)*5)) = -10 
 * (((2*3)-4)*5) = 10
 */

#include "MyMisc.h"

#include <vector>
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Solution {
public:
    std::vector<int> diffWaysToCompute(std::string input) {
        int number = 0;
        if (tryIfNumber(input, &number)) {
            return {number};
        }
        std::vector<int> result;
        for (auto i = 0; i < input.size(); ++i) {
            auto c = input[i];
            if (isOperator(c)) {
                auto leftResult = diffWaysToCompute(input.substr(0, i));
                auto rightResult = diffWaysToCompute(input.substr(i+1));
                for (const auto &left : leftResult) {
                    for (const auto &right : rightResult) {
                        if (c == '+') {
                            result.emplace_back(left + right);
                        } else if (c == '-') {
                            result.emplace_back(left - right);
                        } else if (c == '*') {
                            result.emplace_back(left * right);
                        }
                    }
                }
            }
        }
        return result;
    }

private:
    bool tryIfNumber(const std::string &str, int *number) const {
        *number = 0;
        for (const auto &c : str) {
            if (std::isdigit(c)) {
                *number = *number * 10 + (c - '0');
            } else {
                *number = 0;
                return false;
            }
        }
        return true;
    }

    bool isOperator(const char &c) const {
        return c == '+' || c == '-' || c == '*';
    }
};

int main() {
    Solution sln;

    std::vector<std::string> inputs{"2-1-1", "2*3-4*5"};

    auto print_v = [](const std::vector<int> &computes) {
        std::cout << "[";
        for (const auto &c : computes) {
            std::cout << c << ", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &input : inputs) {
        TestCount();
        print_v(sln.diffWaysToCompute(input));
    }
}