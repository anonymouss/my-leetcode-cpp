/**
 * Given an input string (s) and a pattern (p), implement regular expression
 * matching with support for
 * '.' and '*'.
 * - '.' Matches any single character.
 * - '*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 *
 * Note:
 * s could be empty and contains only lowercase letters a-z.
 * p could be empty and contains only lowercase letters a-z, and characters like
 * `.` or `*`.
 *
 * Example 1:
 * Input:
 * s = "aa"
 * p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 *
 * Example 2:
 * Input:
 * s = "aa"
 * p = "a*"
 * Output: true
 * Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore,
 * by repeating 'a' once, it becomes "aa".
 *
 * Example 3:
 * Input:
 * s = "ab"
 * p = ".*"
 * Output: true
 * Explanation: ".*" means "zero or more (*) of any character (.)".
 *
 * Example 4:
 * Input:
 * s = "aab"
 * p = "c*a*b"
 * Output: true
 * Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore
 * it matches "aab".
 *
 * Example 5:
 * Input:
 * s = "mississippi"
 * p = "mis*is*p*."
 * Output: false
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

enum class Result : uint32_t {
    NONE,
    TRUE,
    FALSE,
};

#define COMPILE_VERSION 2

#if (COMPILE_VERSION == 0)
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();

        // first character
        bool firstMatch = (!s.empty() && (p[0] == s[0] || p[0] == '.'));

        if (p.length() >= 2 && p[1] == '*') {
            //     occurance 0
            return isMatch(s, p.substr(2))
            //      ||  occurance >= 1
                    || (firstMatch && isMatch(s.substr(1), p));
        } else {
            return firstMatch && isMatch(s.substr(1), p.substr(1));
        }
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    bool isMatch(string s, string p) {
        auto sSize = s.length() + 1, pSize = p.length() + 1;
        memo.resize(sSize);
        for (auto i = 0; i < sSize; ++i) {
            memo[i].resize(pSize);
            memo[i].assign(pSize, Result::NONE);
        }
        return dp(0, 0, s, p);
    }

private:
    vector<vector<Result>> memo;
    bool dp(int i, int j, string &s, string &p) {
        if (memo[i][j] != Result::NONE) {
            return memo[i][j] == Result::TRUE;
        }
        bool res;
        if (j == p.length()) {
            res = i == s.length();
        } else {
            bool firstMatch = (i < s.length() &&
                              (p[j] == s[i] ||
                               p[j] == '.'));
            if (j + 1 < p.length() && p[j + 1] == '*') {
                res = (dp(i, j + 2, s, p) ||
                        firstMatch && dp(i + 1, j, s, p));
            } else {
                res = firstMatch && dp(i + 1, j + 1, s, p);
            }
        }
        memo[i][j] = res ? Result::TRUE : Result::FALSE;
        return res;
    }
};
#elif (COMPILE_VERSION == 2)
class Solution {
public:
    bool isMatch(string s, string p) {
        auto sLen = s.length(), pLen = p.length();
        vector<vector<bool>> dp(sLen + 1, vector<bool>(pLen + 1));
        dp[sLen][pLen] = true;

        for (int i = sLen; i >= 0; --i) {
            for (int j = pLen - 1; j >= 0; --j) {
                bool firstMatch = (i < sLen &&
                                  (p[j] == s[i] ||
                                   p[j] == '.'));
                if (j + 1 < pLen && p[j + 1] == '*') {
                    dp[i][j] = dp[i][j + 2] || firstMatch && dp[i + 1][j];
                } else {
                    dp[i][j] = firstMatch && dp[i + 1][j + 1];
                }
            }
        }
        return dp[0][0];
    }
};
#endif

int main() {
    Solution s;

    string s1{"aa"}, p1{"a"};                   // expect `false`
    string s2{"aa"}, p2{"a*"};                  // expect `true`
    string s3{"ab"}, p3{".*"};                  // expect `true`
    string s4{"aab"}, p4{"c*a*b"};              // expect `true`
    string s5{"mississippi"}, p5{"mis*is*p*"};  // expect `false`
    string s6{"aaa"}, p6{"aaaa"};               // expect `false`
    string s7{"aaa"}, p7{"a*a"};                // expect `true`

    std::cout << std::boolalpha;
    std::cout << "Case 1: " << s.isMatch(s1, p1) << std::endl;
    std::cout << "Case 2: " << s.isMatch(s2, p2) << std::endl;
    std::cout << "Case 3: " << s.isMatch(s3, p3) << std::endl;
    std::cout << "Case 4: " << s.isMatch(s4, p4) << std::endl;
    std::cout << "Case 5: " << s.isMatch(s5, p5) << std::endl;
    std::cout << "Case 6: " << s.isMatch(s6, p6) << std::endl;
    std::cout << "Case 7: " << s.isMatch(s7, p7) << std::endl;
}