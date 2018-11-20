/**
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return the minimum cuts needed for a palindrome partitioning of s.
 *
 * Example:
 * Input: "aab"
 * Output: 1
 * Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::min;

class Solution {
public:
    int minCut(string s) {
        int n = s.length();
        vector<int> cut(n + 1, 0);
        for (int i = 0; i <= n; i++) cut[i] = i-1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; i - j >= 0 && i + j < n && s[i - j] == s[i + j]; ++j)
                cut[i + j + 1] = min(cut[i + j + 1], 1 + cut[i - j]);

            for (int j = 1; i - j + 1 >= 0 && i + j < n && s[i - j + 1] == s[i + j]; ++j)
                cut[i + j + 1] = min(cut[i + j + 1], 1 + cut[i - j + 1]);
        }
        return cut[n];
    }
};

int main() {
    Solution s;

    vector<string> strs{
        "aab",
        "",
        "a",
        "bb",
        "abaccde", // 3
        "apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruqdkeiszrlmtwgfxyfostpqczidfljwfbbrflkgdvtytbgq"
        "alguewnhvvmcgxboycffopmtmhtfizxkmeftcucxpobxmelmjtuzigsxnncxpaibgpuijwhankxbplpyejxmrrjgeo"
        "evqozwdtgospohznkoyzocjlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwtxcukwplgtobhgxukwrdlszf"
        "aiqxwjvrgxnsveedxseeyeykarqnjrtlaliyudpacctzizcftjlunlgnfwcqqxcqikocqffsjyurzwysfjmswvhbrm"
        "shjuzsgpwyubtfbnwajuvrfhlccvfwhxfqthkcwhatktymgxostjlztwdxritygbrbibdgkezvzajizxasjnrcjwzd"
        "fvdnwwqeyumkamhzoqhnqjfzwzbixclcxqrtniznemxeahfozp"
    };

    for (auto &str : strs) {
        TestCount();
        auto cut = s.minCut(str);
        std::cout << cut << std::endl;
    }
}