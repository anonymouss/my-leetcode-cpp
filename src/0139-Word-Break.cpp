/**
 * Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
 * determine if s can be segmented into a space-separated sequence of one or more dictionary words.
 *
 * Note:
 * - The same word in the dictionary may be reused multiple times in the segmentation.
 * - You may assume the dictionary does not contain duplicate words.
 *
 * Example 1:
 * Input: s = "leetcode", wordDict = ["leet", "code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet code".
 *
 * Example 2:
 * Input: s = "applepenapple", wordDict = ["apple", "pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
 *              Note that you are allowed to reuse a dictionary word.
 *
 * Example 3:
 * Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
 * Output: false
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>

using std::string;
using std::vector;
using std::pair;
using std::unordered_set;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (s.empty()) return true;
        vector<bool> dp(s.length() + 1, false);
        dp[0] = true;
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

        for (int i = 0; i < s.length(); ++i) {
            for (int j = i; j >= 0; --j) {
                auto cs = s.substr(j, i - j + 1);
                if (wordSet.count(cs)) {
                    dp[i+1] = dp[i+1] || dp[j];
                }
                if (dp[i+1]) break;
            }
        }

        return dp.back();
    }
};

int main() {
    Solution s;

    vector<pair<string, vector<string>>> inputs {
        {
            "leetcode",
            {"leet", "code"}
        },
        {
            "applepenapple",
            {"apple", "pen"}
        },
        {
            "catsandog",
            {"cats", "dog", "sand", "and", "cat"}
        }
    };

    for (auto &p : inputs) {
        TestCount(IOFormat::BOOL);
        auto canBreak = s.wordBreak(p.first, p.second);
        std::cout << canBreak << std::endl;
    }
}