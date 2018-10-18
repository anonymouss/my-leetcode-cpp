/**
 * Given an input string (s) and a pattern (p), implement wildcard pattern
 * matching with support for '?' and '*'.
 * - '?' Matches any single character.
 * - '*' Matches any sequence of characters (including the empty sequence).
 * The matching should cover the entire input string (not partial).
 *
 * Note:
 * `s` could be empty and contains only lowercase letters `a-z`.
 * `p` could be empty and contains only lowercase letters `a-z`, and characters
 * like `?` or `*`.
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
 * p = "*"
 * Output: true
 * Explanation: '*' matches any sequence.
 *
 * Example 3:
 * Input:
 * s = "cb"
 * p = "?a"
 * Output: false
 * Explanation: '?' matches 'c', but the second letter is 'a', which does not
 * match 'b'.
 *
 * Example 4:
 * Input:
 * s = "adceb"
 * p = "*a*b"
 * Output: true
 * Explanation: The first '*' matches the empty sequence, while the second '*'
 * matches the substring "dce".
 *
 * Example 5:
 * Input:
 * s = "acdcb"
 * p = "a*c?b"
 * Output: false
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

#define COMPILE_VERSION 2

#if (COMPILE_VERSION == 0)
class Solution {
public:
    bool isMatch(string s, string p) {
        int sIndex = 0, pIndex = 0, starIndex = -1, matchStartIndex = 0;
        while (sIndex < s.length()) {
            if (pIndex < p.length()
                    && (p[pIndex] == s[sIndex] || p[pIndex] == '?')) {
                // matched! next
                ++sIndex;
                ++pIndex;
            } else if (pIndex < p.length() && p[pIndex] == '*') {
                // find '*', mark the position for backtracking
                starIndex = pIndex;
                ++pIndex;
                matchStartIndex = sIndex;
            } else if (starIndex != -1) {
                // backtracking
                pIndex = starIndex + 1;
                ++matchStartIndex;
                sIndex = matchStartIndex;
            } else {
                // unmatched and no '*' found
                return false;
            }
        }
        // skip remaning '*'
        while (pIndex < p.length() && p[pIndex] == '*') ++pIndex;
        return pIndex == p.length();
    }
};
#elif (COMPILE_VERSION == 1)
// TLE
class Solution {
public:
    bool isMatch(string s, string p) {
        return dfs(s, p, 0, 0);
    }

    bool dfs(string &s, string &p, int sIndex, int pIndex) {
        if (pIndex == p.length()) return sIndex == s.length();
        if (p[pIndex] == '*') {
            // find first non-'*' character
            while(pIndex < p.length() && p[pIndex] == '*') ++pIndex;
            while (sIndex < s.length()) {
                if (dfs(s, p, sIndex, pIndex)) return true;
                ++sIndex; // try next
            }
            return dfs(s, p, sIndex, pIndex);
        } else if (sIndex < s.length()
                && (p[pIndex] == '?' || p[pIndex] == s[sIndex])) {
            return dfs(s, p, sIndex + 1, pIndex + 1);
        } else {
            return false;
        }
    }
};
#elif (COMPILE_VERSION == 2)
// dp
class Solution {
public:
    bool isMatch(string s, string p) {
        int sLen = s.length(), pLen = p.length();
        vector<vector<bool>> dp(sLen + 1, vector<bool>(pLen + 1, false));
        dp[0][0] = true;
        for (int pIndex = 1; pIndex <= p.length(); ++pIndex)
            dp[0][pIndex] = dp[0][pIndex - 1] && (p[pIndex - 1] == '*');
        for (int sIndex = 1; sIndex <= s.length(); ++sIndex) {
            for (int pIndex = 1; pIndex <= p.length(); ++pIndex) {
                if (p[pIndex - 1] == '?' || p[pIndex - 1] == s[sIndex - 1])
                    dp[sIndex][pIndex] = dp[sIndex - 1][pIndex - 1];
                else if (p[pIndex - 1] == '*')
                    dp[sIndex][pIndex] =
                        dp[sIndex - 1][pIndex] || dp[sIndex][pIndex - 1];
            }
        }
        return dp[sLen][pLen];
    }
};
#endif

int main() {
    Solution solution;
    int testId = 1;

    vector<string> s{
        "aa",       // s1
        "aa",       // s2
        "cb",       // s3
        "adceb",    // s4
        "acdcb",    // s5
        "b",        // s6
        "adceb",    // s7
        "abce"      // s8
    };

    vector<string> p{
        "a",        // p1, expect false
        "*",        // p2, expect true
        "?a",       // p3, expect false
        "a*b",      // p4, expect true
        "a*c?b",    // p5, expect false
        "?*?",      // p6, expect false
        "*a*b",     // p7, expect true
        "abc*d"     // p8, expect false
    };

    if (s.size() != p.size()) {
        std::cout << "incorrect test cases, exit" << std::endl;
        return -1;
    }

    for (int i = 0; i < s.size(); ++i) {
        auto ret = solution.isMatch(s[i], p[i]);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << ret << std::endl;
    }
}