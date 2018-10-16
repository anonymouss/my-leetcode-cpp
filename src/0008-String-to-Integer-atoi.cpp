/**
 * Implement `atoi` which converts a `string` to an `integer`.
 *
 * The function first discards as many whitespace characters as necessary until
 * the first non-whitespace character is found. Then, starting from this
 * character, takes an optional initial plus or minus sign followed by as many
 * numerical digits as possible, and interprets them as a numerical value.
 *
 * The string can contain additional characters after those that form the
 * integral number, which are ignored and have no effect on the behavior of this
 * function.
 *
 * If the first sequence of non-whitespace characters in str is not a valid
 * integral number, or if no such sequence exists because either str is empty or
 * it contains only whitespace characters, no conversion is performed.
 *
 * If no valid conversion could be performed, a zero value is returned.
 *
 * Note:
 * Only the space character ' ' is considered as whitespace character.
 * Assume we are dealing with an environment which could only store integers
 * within the 32-bit signed integer range: [−2^31,  2^31 − 1]. If the numerical
 * value is out of the range of representable values, INT_MAX (2^31 − 1) or
 * INT_MIN (−2^31) is returned.
 * 
 * Example 1:
 * Input: "42"
 * Output: 42
 * 
 * Example 2:
 * Input: "   -42"
 * Output: -42
 * Explanation: The first non-whitespace character is '-', which is the minus
 *              sign.
 *              Then take as many numerical digits as possible, which gets 42.
 * 
 * Example 3:
 * Input: "4193 with words"
 * Output: 4193
 * Explanation: Conversion stops at digit '3' as the next character is not a
 * numerical digit.
 * 
 * Example 4:
 * Input: "words and 987"
 * Output: 0
 * Explanation: The first non-whitespace character is 'w', which is not a
 *              numerical digit or a +/- sign. Therefore no valid conversion
 *              could be performed.
 * 
 * Example 5:
 * Input: "-91283472332"
 * Output: -2147483648
 * Explanation: The number "-91283472332" is out of the range of a 32-bit signed
 *              integer. Thefore INT_MIN (−2^31) is returned.
 */

#include <iostream>
#include <string>
#include <cctype>

using std::string;
using std::isdigit;

class Solution {
public:
    int myAtoi(string str) {
        bool isStarted = false;
        bool isNegative = false;
        int res = 0;
        for (const auto &ch : str) {
            if (isStarted && !isdigit(ch)) break;
            if (ch == ' ') continue;
            isStarted = true;
            if (isdigit(ch)) {
                int v = ch - '0';
                if (isNegative && -res  < (INT32_MIN + v) / 10) {
                    return INT32_MIN;
                } else if (!isNegative && res > (INT32_MAX - v) / 10) {
                    return INT32_MAX;
                }
                res = res * 10 + v;
            } else if (ch == '-') isNegative = true;
            else if (ch == '+') continue;
            else break;
        }
        return isNegative ? -res : res;
    }
};

int main() {
    Solution s;

    string s1{"42"};
    string s2{"   -42"};
    string s3{"4193 with words"};
    string s4{"words and 987"};
    string s5{"-91283472332"};
    string s6{"-01324000"};

    std::cout << "Case 1: " << s.myAtoi(s1) << std::endl;
    std::cout << "Case 2: " << s.myAtoi(s2) << std::endl;
    std::cout << "Case 3: " << s.myAtoi(s3) << std::endl;
    std::cout << "Case 4: " << s.myAtoi(s4) << std::endl;
    std::cout << "Case 5: " << s.myAtoi(s5) << std::endl;
    std::cout << "Case 6: " << s.myAtoi(s6) << std::endl;
}