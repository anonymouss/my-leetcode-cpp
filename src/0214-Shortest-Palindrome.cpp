/**
 * Given a string s, you are allowed to convert it to a palindrome by adding characters in front of
 * it. Find and return the shortest palindrome you can find by performing this transformation.
 *
 * Example 1:
 * Input: "aacecaaa"
 * Output: "aaacecaaa"
 *
 * Example 2:
 * Input: "abcd"
 * Output: "dcbabcd"
 */

#include "MyMisc.h"

#include <iostream>
#include <string>
#include <vector>

#define BRUTE_FORCE 0
#define TWO_POINTERS 1
#define KMP_METHOD 2

#define COMPILE_VERSION KMP_METHOD

#if (COMPILE_VERSION == BRUTE_FORCE)  // Exceeds memory limit
class Solution {
public:
    std::string shortestPalindrome(std::string s) {
        auto r = s;
        std::reverse(r.begin(), r.end());
        auto n = s.length();
        std::string res;
        auto i = 0;
        for (; i < n; ++i) {
            if (s.substr(0, n - i) == r.substr(i)) {
                res = r.substr(0, i) + s;
                break;
            }
        }
        if (i == n) res = (r.substr(0, n - 1) + s);
        return res;
    }
};
#elif (COMPILE_VERSION == TWO_POINTERS)
class Solution {
public:
    std::string shortestPalindrome(std::string s) {
        auto n = s.length();
        auto i = 0;
        for (int j = n - 1; j >= 0; --j) {
            if (s[i] == s[j]) ++i;
        }
        if (i == n) return s;
        auto r = s.substr(i, n);
        std::reverse(r.begin(), r.end());
        return r + shortestPalindrome(s.substr(0, i)) + s.substr(i);
    }
};
#elif (COMPILE_VERSION == KMP_METHOD)
class Solution {
public:
    std::string shortestPalindrome(std::string s) {
        int n = s.size();
        std::string rev(s);
        std::reverse(rev.begin(), rev.end());
        std::string s_new = s + "#" + rev;
        int n_new = s_new.size();
        std::vector<int> f(n_new, 0);
        for (int i = 1; i < n_new; i++) {
            int t = f[i - 1];
            while (t > 0 && s_new[i] != s_new[t]) t = f[t - 1];
            if (s_new[i] == s_new[t]) ++t;
            f[i] = t;
        }
        return rev.substr(0, n - f[n_new - 1]) + s;
    }
};
#endif

int main() {
    Solution sln;

    std::vector<std::string> ss{"aacecaaa", "abcd", "aba", "aaaabcdaaaee"};

    for (auto &s : ss) {
        TestCount();
        std::cout << (sln.shortestPalindrome(s)) << std::endl;
    }
}