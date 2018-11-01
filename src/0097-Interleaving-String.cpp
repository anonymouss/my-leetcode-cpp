/**
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 *
 * Example 1:
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
 * Output: true
 *
 * Example 2:
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
 * Output: false
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::sort;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
// TLE
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // incorrect length
        if ((s1.length() + s2.length()) != s3.length()) return false;
        if (s3.empty()) return true;
        // different elements, no need to continue checking
        auto st1 = s1 + s2, st2 = s3;
        sort(st1.begin(), st1.end()); sort(st2.begin(), st2.end());
        if (st1 != st2) return false;
        auto res = false;
        // recursion
        if (!s1.empty() && s1[0] == s3[0])
            res = isInterleave(s1.substr(1), s2, s3.substr(1));
        if (!res && !s2.empty() && s2[0] == s3[0])
            res = isInterleave(s1, s2.substr(1), s3.substr(1));
        return res;
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.length() + s2.length() != s3.length()) return false;
        vector<vector<bool>> dp(s1.length()+1, vector<bool>(s2.length()+1, false));
        for (int i = 0; i <= s1.length(); ++i) {
            for (int j = 0; j <= s2.length(); ++j) {
                if (i == 0 && j == 0) dp[i][j] = true;
                else if (i == 0)
                    dp[i][j] = dp[i][j-1] && s2[j-1] == s3[i+j-1];
                else if (j == 0)
                    dp[i][j] = dp[i-1][j] && s1[i-1] == s3[i+j-1];
                else
                    dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) ||
                        (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        return dp[s1.length()][s2.length()];
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<vector<string>> strs{
        // s1, s2, s3
        {"aabcc", "dbbca", "aadbbcbcac"},       // true
        {"dbbca", "aabcc", "aadbbcbcac"},       // true
        {"aabcc", "dbbca", "aadbbbaccc"},       // false
        // TLE case
        {"bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbab"
        "abbabaabababbbaabababababbbaaababaa",

        "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaa"
        "baabbbbbbbbbbbabaaabbababbabbabaab",

        "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaa"
        "abababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaa"
        "abbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab"}
    };

    for (auto sv: strs) {
        auto res = s.isInterleave(sv[0], sv[1], sv[2]);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}