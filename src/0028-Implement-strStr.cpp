/**
 * Implement strStr().
 * Return the index of the first occurrence of needle in haystack, or -1 if
 * needle is not part of haystack.
 *
 * Example 1:
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 *
 * Example 2:
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 *
 * Clarification:
 * What should we return when needle is an empty string? This is a great
 * question to ask during an interview.
 * For the purpose of this problem, we will return 0 when needle is an empty
 * string. This is consistent to C's strstr() and Java's indexOf().
 */

#include <iostream>
#include <string>

using std::string;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        int hIndex, nIndex, hLen = haystack.length(), nLen = needle.length();
        for (hIndex = nIndex = 0; hIndex < hLen && nIndex < nLen;) {
            if (haystack[hIndex] == needle[nIndex]) {
                ++hIndex, ++nIndex;
            } else {
                hIndex -= nIndex - 1, nIndex = 0;
            }
        }
        return nIndex == nLen ? hIndex - nIndex : -1;
    }
};

int main() {
    Solution s;

    string haystack1{"hello"}, needle1{"ll"};
    string haystack2{"aaaaa"}, needle2{"bba"};

    std::cout << "Case 1: " << s.strStr(haystack1, needle1) << std::endl;
    std::cout << "Case 2: " << s.strStr(haystack2, needle2) << std::endl;
}