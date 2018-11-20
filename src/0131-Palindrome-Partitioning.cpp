/**
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return all possible palindrome partitioning of s.
 *
 * Example:
 * Input: "aab"
 * Output:
 * [
 *   ["aa","b"],
 *   ["a","a","b"]
 * ]
 */

#include "../utils/MyMisc.h"
#include "../utils/MyContainerUtil.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> part;
        divide(s, 0, part, res);
        return res;
    }

    void divide(const string &s, int start, vector<string> &part, vector<vector<string>> &res) {
        if (start == s.length()) {
            res.emplace_back(part);
            return;
        }
        for (int i = start, n = s.length(); i < n; ++i) {
            if (isPalindromic(s, start, i)) {
                part.emplace_back(s.substr(start, i - start + 1));
                divide(s, i + 1, part, res);
                part.pop_back();
            }
        }
    }

    bool isPalindromic(const string &s, int l, int r) {
        while (l < r) {
            if (s[l++] != s[r--]) return false;
        }
        return true;
    }
};

int main() {
    Solution s;

    vector<string> strs{
        "aab",
        ""
    };

    for (auto &str : strs) {
        TestCount();
        auto res = s.partition(str);
        myDispVector2D(res);
    }
}