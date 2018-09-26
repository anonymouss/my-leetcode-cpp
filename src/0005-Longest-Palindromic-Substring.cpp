/**
 * Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
 *
 * Example 1:
 *
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 *
 * Example 2:
 *
 * Input: "cbbd"
 * Output: "bb"
 */

#include "../utils/MyClock.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using std::string;
using std::vector;
using std::memset;

#define COMPILE_VERSION 2

#if (COMPILE_VERSION == 0)
// brute force solution... - TLE
// ??? looks like it's also o(N^2)...
class Solution {
public:
    string longestPalindrome(string s) {
#ifdef DEBUG
        MyClock<MY_MS> myClock;
#endif
        if (s.empty()) return {""};
        auto len = s.length();
        int max = 0;
        string res("");

        for (auto i = 0; i < len; ++i) {
            int maxTmp = 1;
            string tmp{s[i]};
            auto l = i -1, r = i + 1;

            auto expand = [&](int l, int r) {
                while (l >= 0 && r <= len - 1 && s[l] == s[r]) {
                    tmp = s[l] + tmp;
                    tmp = tmp + s[r];
                    maxTmp += 2;
                    --l, ++r;
                }
            };

            auto update = [&]() {
                if (maxTmp > max) {
                    max = maxTmp;
                    res = tmp; // copy
                }
            };

            expand(l, r);
            update();

            if (len > 1 && s[i] == s[i + 1]) {
                tmp.clear();
                tmp = tmp + s[i] + s[i + 1];
                l = i - 1, r = i + 2;
                maxTmp = 2;
                expand(l, r);
            }
            update();

        }
        return res;
    }
};
#elif (COMPILE_VERSION == 1)
// LCS (dynamic programming) - AC
class Solution {
public:
    string longestPalindrome(string s) {
#ifdef DEBUG
        MyClock<MY_MS> myClock;
#endif
        auto len = s.length();
        int max = 0, global_max = 0;
        int rend = -1, end = -1;
        bool inPalindrome = false;
        vector<vector<int>> dp(len, vector<int>(len, 0));
        string res{""};

        // use test case 3 for verification
        auto updateAndClear = [&]() {
            if (inPalindrome && rend + max - 1 == end && max > global_max) {
                // update global vars
                global_max = max;
                res = s.substr(end-max+1, max);
            }
            // clear tmp vars
            max = 0;
        };

        for (int i = 0; i < len; ++i) {
            for (int j = len - 1; j >= 0; --j) {
                if (s[i] == s[j]) {
                    inPalindrome = true;
                    if (i == 0 || j == len - 1) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = dp[i-1][j+1] + 1;
                    }
                    if (dp[i][j] > max) {
                        // update
                        max = dp[i][j];
                        end = i;
                        rend = j;
                    }
                } else {
                    updateAndClear();
                    inPalindrome = false;
                    dp[i][j] = 0;
                }
            }
        }
        updateAndClear();
        return res;
    }
};
#elif (COMPILE_VERSION == 2)
// Manacher's algorithm https://www.felix021.com/blog/read.php?2040 - AC / fastest
// index  0  1  2  3  4  5  6  7  8  9  10 11 12
//                 j       idx       i
// str[]  ?  #  b  #  a  #  b  #  a  #  d  #  ^
//                                   mx
class Solution {
public:
    string longestPalindrome(string s) {
#ifdef DEBUG
        MyClock<MY_MS> myClock;
#endif
        if (s.empty()) return "";
        auto len = s.length();
        auto allocLen = 2 * len + 3;
        char *str = new char[allocLen];
        int *p = new int[allocLen];
        memset(p, 0, allocLen * sizeof(int));
        int mx = 0, idx = 0;

        // prepare
        for (int i = 0, flag = -1; i < allocLen; i++, flag *= -1) {
            if (i == 0) str[i] = '?';
            else if (i == allocLen - 1) str[i] = '^';
            else str[i] = (flag == 1) ? '#' : s[(i-1)/2];
        }

        for (int i = 0; i < allocLen; ++i) {
            if (mx > i) {
                auto j = 2 * idx - i;
                if (p[j] < mx - i)
                    p[i] = p[j];
                else
                    p[i] = mx - i;
            }
            while ((str[i + p[i] + 1] == str[i - p[i] - 1])) ++p[i]; //expand
            if (i + p[i] > mx) {
                mx  = i + p[i];
                idx = i;
            }
        }

        int maxLen = 0, maxIdx = -1;
        for(int i = 0; i < allocLen; ++i) {
            if (p[i] > maxLen) {
                maxLen = p[i];
                maxIdx = i;
            }
        }

        auto start = (maxIdx - p[maxIdx] - 1) / 2;
        delete [] str;
        delete [] p;

        return s.substr(start, p[maxIdx]);
    }
};
#endif

int main() {

    Solution s;
    string s1{"babad"};
    string s2{"cbbd"};
    string s3{"abxyba"};
    string s4(1000, 'a');

    std::cout << "Case 1: " << s.longestPalindrome(s1) << std::endl;
    std::cout << "Case 2: " << s.longestPalindrome(s2) << std::endl;
    std::cout << "Case 3: " << s.longestPalindrome(s3) << std::endl;
    std::cout << "Case 4: " << s.longestPalindrome(s4) << std::endl;
}