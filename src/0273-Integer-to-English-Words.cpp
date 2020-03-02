/**
 * Convert a non-negative integer to its english words representation. Given input is guaranteed to
 * be less than 231 - 1.
 *
 * Example 1:
 * Input: 123
 * Output: "One Hundred Twenty Three"
 *
 * Example 2:
 * Input: 12345
 * Output: "Twelve Thousand Three Hundred Forty Five"
 *
 * Example 3:
 * Input: 1234567
 * Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
 *
 * Example 4:
 * Input: 1234567891
 * Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight
 * Hundred Ninety One"
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <string>

static const std::string kDigit[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
            "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
            "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
static const std::string kXty[] = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", 
            "Seventy", "Eighty", "Ninety"};
static const std::string kScale[] = {"", " Thousand", " Million", " Billion", " Trillion",
            "Quadrillion"};
static const std::string kSmallScale[] = {" Hundred", "", " Ten"};

class Solution {
public:
    std::string numberToWords(int num) {
        if (num == 0) return "Zero";
        std::string result = "";
        int scope = 0;
        while (num) {
            auto token = num % 1000;
            num = num / 1000;
            auto str = stringOfThreeNumber(token);
            if (str != "") str = str + kScale[scope];
            if (result != "" && str != "") result = str + " " + result;
            else if (result == "") result = str;
            ++scope;
        }
        return result;
    }

private:
    std::string stringOfTwoOrLessNumber(int two) {
        if (two < 20) {
            return kDigit[two];
        } else {
            auto tenner = two / 10;
            auto rest = two % 10;
            if (rest != 0) {
                return kXty[tenner] + " " + kDigit[rest];
            } else {
                return kXty[tenner];
            }
        } 
    }

    std::string stringOfThreeNumber(int three) {
        auto hundreder = three / 100;
        auto rest = three % 100;
        if (hundreder != 0 && rest != 0) {
            return kDigit[hundreder] + " Hundred " + stringOfTwoOrLessNumber(rest);
        } else if (hundreder != 0) {
            return kDigit[hundreder] + " Hundred";
        } else if (rest != 0) {
            return stringOfTwoOrLessNumber(rest);
        } else {
            return "";
        }
    }
};

int main() {
    Solution sln;

    std::vector<int> nums{123, 12345, 1234567, 1234567891, 1000010};

    for (auto &num : nums) {
        TestCount();
        std::cout << sln.numberToWords(num) << std::endl;
    }
}