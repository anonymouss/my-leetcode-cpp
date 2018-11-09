/**
 * Given a string S and a string T, count the number of distinct subsequences of S which equals T.
 * A subsequence of a string is a new string which is formed from the original string by deleting
 * some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
 *
 * Example 1:
 * Input: S = "rabbbit", T = "rabbit"
 * Output: 3
 * Explanation: As shown below, there are 3 ways you can generate "rabbit" from S.
 * (The caret symbol ^ means the chosen letters)
 * rabbbit
 * ^^^^ ^^
 * rabbbit
 * ^^ ^^^^
 * rabbbit
 * ^^^ ^^^
 *
 * Example 2:
 * Input: S = "babgbag", T = "bag"
 * Output: 5
 * Explanation: As shown below, there are 5 ways you can generate "bag" from S.
 * (The caret symbol ^ means the chosen letters)
 * babgbag
 * ^^ ^
 * babgbag
 * ^^    ^
 * babgbag
 * ^    ^^
 * babgbag
 *   ^  ^^
 * babgbag
 *     ^^^
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::string;
using std::vector;
using std::pair;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
// TLE
class Solution {
public:
    int numDistinct(string s, string t) {
        if (s.length() < t.length()) return 0;
        if (t.empty()) return 1;
        int i = 0;
        int n = 0;
        for (; i <= (s.length() - t.length()); ++i) {
            if (s[i] == t[0]) {
                if (t.length() == 1) n = 1;
                else n = numDistinct(s.substr(i+1), t.substr(1));
                break;
            }
        }
        return n + (i <= s.length() - t.length() ? numDistinct(s.substr(i+1), t) : 0);
    }
};
#elif (COMPILE_VERSION == 1)
// dp https://www.cnblogs.com/grandyang/p/4294105.html
class Solution {
public:
    int numDistinct(string s, string t) {
        vector<vector<int>> dp(t.length()+1, vector<int>(s.length()+1, 0));
        dp[0].assign(s.length()+1, 1);
        for (int i = 1; i < t.length() + 1; ++i) {
            for (int j = i; j < s.length() + 1; ++j) {
                if (t[i-1] == s[j-1])
                    dp[i][j] = dp[i-1][j-1] + dp[i][j-1];
                else
                    dp[i][j] = dp[i][j-1];
            }
        }
        return dp[t.length()][s.length()];
    }
};
#endif

int main() {
    Solution s;

    vector<pair<string, string>> sts{
        {"rabbbit", "rabbit"},
        {"babgbag", "bag"},
        {"b", "a"}
    };

    for (auto &st : sts) {
        TestCount();
        auto num = s.numDistinct(st.first, st.second);
        std::cout << num << std::endl;
    }
}