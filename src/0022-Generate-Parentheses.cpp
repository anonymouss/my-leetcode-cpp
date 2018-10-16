/**
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 *
 * For example, given n = 3, a solution set is:
 * [
 *   "((()))",
 *   "(()())",
 *   "(())()",
 *   "()(())",
 *   "()()()"
 * ]
 */

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

// Catalan Number : https://en.wikipedia.org/wiki/Catalan_number

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
// backtracking
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        generate(res, "", n, n);
        return res;
    }

    void generate(vector<string>& res, string s, int left, int right) {
        if (left == 0 && right == 0) {
            res.emplace_back(s);
            return;
        }
        if (left > 0) generate(res, s + "(", left - 1, right);
        if (left < right) generate(res, s + ")", left, right - 1);
    }
};
#elif (COMPILE_VERSION == 1)
// closure number
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        if (n == 0) {
            res.emplace_back("");
        } else {
            for (int i = 0; i < n; ++i)
                for (string left : generateParenthesis(i))
                    for (string right : generateParenthesis(n - 1 - i))
                        res.emplace_back("(" + left + ")" + right);
        }
        return res;
    }
};
#endif

int main() {
    Solution s;

    auto exeTest = [&](int n, int testId) {
        auto res = s.generateParenthesis(n);
        std::cout << "Case " << testId << ":\n  [\n";
        for (const auto &s : res) {
            std::cout << "    \"" << s << "\",\n";
        }
        std::cout << "  ]" << std::endl;
    };

    exeTest(1, 1);  // 1
    exeTest(2, 2);  // 2
    exeTest(3, 3);  // 5
    exeTest(4, 4);  // 14
}