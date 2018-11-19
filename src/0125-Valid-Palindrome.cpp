/**
 * Given a string, determine if it is a palindrome, considering only alphanumeric characters and
 * ignoring cases.
 * Note: For the purpose of this problem, we define empty string as valid palindrome.
 *
 * Example 1:
 * Input: "A man, a plan, a canal: Panama"
 * Output: true
 *
 * Example 2:
 * Input: "race a car"
 * Output: false
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while (left <= right) {
            if (!isValidChar(s[left])) {
                ++left;
                continue;
            }
            if (!isValidChar(s[right])) {
                --right;
                continue;
            }
            if (!isSame(s[left], s[right]))
                return false;
            ++left; --right;
        }
        return true;
    }

    bool isValidChar(const char &ch) {
        return isAlpha(ch) || isDigit(ch);
    }

    bool isAlpha(const char &ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    bool isDigit(const char &ch) {
        return (ch >= '0' && ch <= '9');
    }

    bool isSame(const char &ch1, const char &ch2) {
        if (isAlpha(ch1) && isAlpha(ch2))
            return (ch1 == ch2) || (ch1 - ch2 == 32) || (ch2 - ch1 == 32);
        else if (isDigit(ch1) == isDigit(ch2))
            return ch1 == ch2;
        else
            return false;
    }
};

int main() {
    Solution s;

    vector<string> inputs{
        "A man, a plan, a canal: Panama",
        "race a car",
        "0P"
    };

    for (auto &input : inputs) {
        TestCount(IOFormat::BOOL);
        std::cout << s.isPalindrome(input) << std::endl;
    }
}