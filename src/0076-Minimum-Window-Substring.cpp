/**
 * Given a string S and a string T, find the minimum window in S which will contain all the characters
 * in T in complexity O(n).
 *
 * Example:
 * Input: S = "ADOBECODEBANC", T = "ABC"
 * Output: "BANC"
 *
 * Note:
 * - If there is no such window in S that covers all characters in T, return the empty string "".
 * If there is such window, you are guaranteed that there will always be only one unique minimum
 * window in S.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

class Solution {
public:
    string minWindow(string s, string t) {
        string res{""};
        unordered_map<char, int> charCounts;

        // chars count in t, this solution doesn't only consider distinct chars in t, duplicates are
        // also counted, which means, if t contains two 'c', window should contain two as well
        for (auto &c : t) ++charCounts[c];
        int left = 0, right = 0, count = 0, start = 0, min = INT32_MAX;

        while (right < s.size()) {
            if (--charCounts[s[right++]] >= 0) count++;
            // count == t.size() means current left to right contains all chars in t, found a window
            while (count == t.size()) {
                // update min window info (window (start) index and window size (min))
                if (min > right - left) {
                    min = right - left;
                    start = left;
                }
                // slide window left boundary, char count > 0 means new windows doesn't contain all
                // chars in t, decrease count
                if (++charCounts[s[left++]] > 0) --count;
            }
        }

        return min == INT32_MAX ? "" : s.substr(start, min);
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<string>> sts{
        // s, t
        {"ADOBECODEBANC", "ABC"},
        {"ab", "a"}
    };

    for (auto &st : sts) {
        auto window = s.minWindow(st[0], st[1]);
        std::cout << "Case " << testId++ << ": " << window << std::endl;
    }
}