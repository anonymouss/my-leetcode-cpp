/**
 * Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add
 * spaces in s to construct a sentence where each word is a valid dictionary word. Return all such
 * possible sentences.
 *
 * Note:
 * - The same word in the dictionary may be reused multiple times in the segmentation.
 * - You may assume the dictionary does not contain duplicate words.
 *
 * Example 1:
 * Input:
 * s = "catsanddog"
 * wordDict = ["cat", "cats", "and", "sand", "dog"]
 * Output:
 * [
 *   "cats and dog",
 *   "cat sand dog"
 * ]
 *
 * Example 2:
 * Input:
 * s = "pineapplepenapple"
 * wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
 * Output:
 * [
 *   "pine apple pen apple",
 *   "pineapple pen apple",
 *   "pine applepen apple"
 * ]
 * Explanation: Note that you are allowed to reuse a dictionary word.
 *
 * Example 3:
 * Input:
 * s = "catsandog"
 * wordDict = ["cats", "dog", "sand", "and", "cat"]
 * Output:
 * []
 */

#include "../utils/MyMisc.h"
#include "../utils/MyContainerUtil.h"

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

using std::string;
using std::vector;
using std::pair;
using std::unordered_map;

class Solution {
public:
    unordered_map<string, vector<string>> map;
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if (s.empty()) return {""};
        if (map.count(s)) return map[s];
        vector<string> brk;
        for (auto &word : wordDict) {
            if (s.substr(0, word.length()) != word) continue;
            auto res = wordBreak(s.substr(word.length()), wordDict);
            for (auto &w : res) {
                brk.emplace_back(word + (w.empty() ? "" : " ") + w);
            }
        }
        return map[s] = brk;
    }
};

int main() {
    Solution s;

    vector<pair<string, vector<string>>> inputs {
        {
            "catsanddog",
            {"cat", "cats", "and", "sand", "dog"}
        },
        {
            "pineapplepenapple",
            {"apple", "pen", "applepen", "pine", "pineapple"}
        },
        {
            "catsandog",
            {"cats", "dog", "sand", "and", "cat"}
        }
    };

    for (auto &p : inputs) {
        TestCount();
        auto breaks = s.wordBreak(p.first, p.second);
        myDispVector1D(breaks);
    }
}