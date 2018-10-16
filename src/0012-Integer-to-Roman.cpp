/**
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D
 * and M.
 * Symbol       Value
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 *
 * For example, two is written as II in Roman numeral, just two one's added
 * together. Twelve is written as, XII, which is simply X + II. The number
 * twenty seven is written as XXVII, which is XX + V + II.
 *
 * Roman numerals are usually written largest to smallest from left to right.
 * However, the numeral for four is not IIII. Instead, the number four is
 * written as IV. Because the one is before the five we subtract it making four.
 * The same principle applies to the number nine, which is written as IX. There
 * are six instances where subtraction is used:
 *
 * I can be placed before V (5) and X (10) to make 4 and 9.
 * X can be placed before L (50) and C (100) to make 40 and 90.
 * C can be placed before D (500) and M (1000) to make 400 and 900.
 *
 * Given an integer, convert it to a roman numeral. Input is guaranteed to be
 * within the range from 1 to 3999.
 *
 * Example 1:
 * Input: 3
 * Output: "III"
 *
 * Example 2:
 * Input: 4
 * Output: "IV"
 *
 * Example 3:
 * Input: 9
 * Output: "IX"
 *
 * Example 4:
 * Input: 58
 * Output: "LVIII"
 * Explanation: C = 100, L = 50, XXX = 30 and III = 3.
 *
 * Example 5:
 * Input: 1994
 * Output: "MCMXCIV"
 * Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 */

#include <iostream>
#include <string>

using std::string;

class Solution {
public:
    string intToRoman(int num) {
        string res{""};
        int base = 1;
        while(num) {
            int val = num % 10;
            res = parseInBase(val, base) + res;
            base *= 10;
            num /= 10;
        }
        return res;
    }

    string parse(int val, char base, char fifth, char tenth) {
        if (val < 4) return string(val, base);
        else if (val == 4) return string(1, base) + fifth;
        else if (val < 9) return string(1, fifth) + string(val - 5, base);
        else return string(1, base) + tenth;
    }

    string parseInBase(int val, int base) {
        switch (base) {
            case 1:
                return parse(val, 'I', 'V', 'X');
            case 10:
                return parse(val, 'X', 'L', 'C');
            case 100:
                return parse(val, 'C', 'D', 'M');
            case 1000:
                return parse(val, 'M', '?', '?');
            default:
                return "";
        }
    }
};

int main() {
    Solution s;

    std::cout << "Case 1: " << s.intToRoman(3) << std::endl;
    std::cout << "Case 2: " << s.intToRoman(4) << std::endl;
    std::cout << "Case 3: " << s.intToRoman(9) << std::endl;
    std::cout << "Case 4: " << s.intToRoman(58) << std::endl;
    std::cout << "Case 5: " << s.intToRoman(1994) << std::endl;
}