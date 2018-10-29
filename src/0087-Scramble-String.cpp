/**
 * Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty
 * substrings recursively.
 *
 * Below is one possible representation of s1 = "great":
 *     great
 *    /    \
 *   gr    eat
 *  / \    /  \
 * g   r  e   at
 *            / \
 *           a   t
 * To scramble the string, we may choose any non-leaf node and swap its two children.
 *
 * For example, if we choose the node "gr" and swap its two children, it produces a scrambled string
 * "rgeat".
 *     rgeat
 *    /    \
 *   rg    eat
 *  / \    /  \
 * r   g  e   at
 *            / \
 *           a   t
 * We say that "rgeat" is a scrambled string of "great".
 *
 * Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled
 * string "rgtae".
 *     rgtae
 *    /    \
 *   rg    tae
 *  / \    /  \
 * r   g  ta  e
 *        / \
 *       t   a
 * We say that "rgtae" is a scrambled string of "great".
 *
 * Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
 *
 * Example 1:
 * Input: s1 = "great", s2 = "rgeat"
 * Output: true
 *
 * Example 2:
 * Input: s1 = "abcde", s2 = "caebd"
 * Output: false
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::sort;

#define COMPILE_VERSION 0

#if (COMPILE_VERSION == 0)
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1.length() != s2.length()) return false;
        if (s1 == s2) return true;
        // different elements, no need continue to waste time...
        auto st1 = s1, st2 = s2;
        sort(st1.begin(), st1.end());
        sort(st2.begin(), st2.end());
        if (st1 != st2) return false;
        for (int i = 1; i < s1.length(); ++i) {
            // divide s1[...][.....], s2[...][.....]
            auto s11 = s1.substr(0, i), s12 = s1.substr(i);
            auto s21 = s2.substr(0, i), s22 = s2.substr(i);
            if (isScramble(s11, s21) && isScramble(s12, s22)) return true;
            // divide s1[...][.....], s2[.....][...]
            s21 = s2.substr(s1.length() - i);
            s22 = s2.substr(0, s1.length() - i);
            if (isScramble(s11, s21) && isScramble(s12, s22)) return true;
        }
        return false;
    }
};
#elif (COMPILE_VERSION == 1)
// dp
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1.length() != s2.length()) return false;
        if (s1 == s2) return true;
        int n = s1.length();
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n+1, false)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j][1] = s1[i] == s2[j];
            }
        }
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n-len; ++i) {
                for (int j = 0; j <= n-len; ++j) {
                    for (int k = 1; k < len; ++k) {
                        if ((dp[i][j][k] && dp[i+k][j+k][len-k])
                                || (dp[i+k][j][len-k] && dp[i][j+len-k][k]))
                            dp[i][j][len] = true;
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<vector<string>> strs{
        {"great", "rgeat"},     // true
        {"abcde", "caebd"},     // false
        {"abc", "acb"},         // true
        {"abb", "bab"},         // true
        {"abc", "bca"},         // true
        {"abcde", "caebd"}      // false
    };

    for (auto &str : strs) {
        auto res = s.isScramble(str[0], str[1]);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}