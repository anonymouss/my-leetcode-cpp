/**
 * A message containing letters from A-Z is being encoded to numbers using the following mapping:
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given a non-empty string containing only digits, determine the total number of ways to decode it.
 *
 * Example 1:
 * Input: "12"
 * Output: 2
 * Explanation: It could be decoded as "AB" (1 2) or "L" (12).
 *
 * Example 2:
 * Input: "226"
 * Output: 3
 * Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        vector<int> dp(s.length() + 1, 0);
        dp[0] = 1;
        for (int i = 1; i < dp.size(); ++i) {
            // i-1 is current char
            dp[i] = s[i-1] == '0' ? 0 : dp[i-1]; // consider current char as one number
            if (i > 1 && (s[i-2] == '1' || (s[i-2] == '2' && s[i-1] <= '6')))
                dp[i] += dp[i-2]; // if current char can be combined with prev char as a number
        }
        return dp.back();
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<string> strs{
        "12",
        "226",
        "0000226",
        "10"
    };

    for (auto &str : strs) {
        auto num = s.numDecodings(str);
        std::cout << "Case " << testId++ << ": " << num << std::endl;
    }
}