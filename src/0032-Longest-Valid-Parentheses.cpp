/**
 * Given a string containing just the characters '(' and ')', find the length of
 * the longest valid (well-formed) parentheses substring.
 *
 * Example 1:
 * Input: "(()"
 * Output: 2
 * Explanation: The longest valid parentheses substring is "()"
 *
 * Example 2:
 * Input: ")()())"
 * Output: 4
 * Explanation: The longest valid parentheses substring is "()()"
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using std::string;
using std::vector;
using std::stack;

#define COMPILE_VERSION 2

#if (COMPILE_VERSION == 0)
// dp
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.empty()) return 0;
        int size = s.size(), max = 0;
        vector<int> dp(size, 0);

        auto updateMax = [&](int val) {
            if (val > max) max = val;
        };

        for (int i = 1; i < size; ++i) {
            if (s[i] == ')' && s[i - 1] == '(') {
                dp[i] = ((i > 2) ? dp[i - 2] : 0) + 2;
                updateMax(dp[i]);
            } else if (s[i] == ')' && s[i - 1] == ')'
                    && s[i - dp[i - 1] - 1] == '(') {
                dp[i] = dp[i - 1] + ((i > 2) ? dp[i - dp[i - 1] - 2] : 0) + 2;
                updateMax(dp[i]);
            }
      }
      return max;
    }
};
#elif (COMPILE_VERSION == 1)
// stack
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk; stk.push(-1);
        int max = 0, size = s.length();
        for (int i = 0; i < size; ++i) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                } else {
                    auto v = i - stk.top();
                    max = max > v ? max : v;
                }
            }
        }
        return max;
    }
};
#elif (COMPILE_VERSION == 2)
// traverse twice
class Solution {
public:
    int longestValidParentheses(string s) {
        int lefts = 0, rights = 0, size = s.length(), max = 0;
        // left -> right
        for (int i = 0; i < size; ++i) {
            if (s[i] == '(') ++lefts;
            else ++rights;
            if (lefts == rights)
                max = max > lefts + rights ? max : lefts + rights;
            if (rights > lefts) lefts = 0, rights = 0;
        }
        // right -> left
        lefts = 0, rights = 0;
        for (int i = size - 1; i >= 0; --i) {
            if (s[i] == '(') ++lefts;
            else ++rights;
            if (lefts == rights)
                max = max > lefts + rights ? max : lefts + rights;
            if (lefts > rights) lefts = 0, rights = 0;
        }
        return max;
    }
};
#endif

int main() {
    Solution solution;
    static int testId = 1;

    string s1{"(()"};
    string s2{")()())"};
    string s3{"()(()"};

    auto exeTest = [&](string &s) {
        std::cout << "Case " << testId << ": "
                << solution.longestValidParentheses(s) << std::endl;
        ++testId;
    };

    exeTest(s1);
    exeTest(s2);
    exeTest(s3);
}