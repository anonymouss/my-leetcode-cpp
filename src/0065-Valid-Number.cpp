/**
 * Validate if a given string can be interpreted as a decimal number.
 *
 * Some examples:
 * "0" => true
 * " 0.1 " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 * " -90e3   " => true
 * " 1e" => false
 * "e3" => false
 * " 6e-1" => true
 * " 99e2.5 " => false
 * "53.5e93" => true
 * " --6 " => false
 * "-+3" => false
 * "95a54e53" => false
 *
 * Note: It is intended for the problem statement to be ambiguous. You should gather all
 * requirements up front before implementing one. However, here is a list of characters that can be
 * in a valid decimal number:
 * - Numbers 0-9
 * - Exponent - "e"
 * - Positive/negative sign - "+"/"-"
 * - Decimal point - "."
 * Of course, the context of these characters also matters in the input.
*/

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    bool isNumber(string s) {
        int start = 0, end = s.length() - 1;
        while(start <= end && s[start] == ' ') ++start;
        while(end >= start && s[end] == ' ') --end;
        if (end < start) return false;
        s = s.substr(start, end - start + 1);
        bool eFound = false, dotFound = false, numFound = false, numAfterEFound = false;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] <= '9' && s[i] >= '0') {
                numFound = true;
                numAfterEFound = true;
            } else if (s[i] == '+' || s[i] == '-') {
                if (i != 0 && s[i-1] != 'e') return false;
            } else if (s[i] == 'e') {
                if (!numFound || eFound) return false;
                eFound = true;
                numAfterEFound = false;
            } else if (s[i] == '.') {
                if (dotFound || eFound) return false;
                dotFound = true;
            } else {
                return false;
            }
        }
        return numAfterEFound;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<string> inputs{
        "0",            // true
        " 0.1 ",        // true
        "abc",          // false
        "1 a",          // false
        "2e10",         // true
        " -90e3   ",    // true
        " 1e",          // false
        "e3",           // false
        " 6e-1",        // true
        " 99e2.5 ",     // false
        "53.5e93",      // true
        " --6 ",        // false
        "-+3",          // false
        "95a54e53",     // false
        ".1",           // true
        "."             // false
    };

    for (auto &input : inputs) {
        auto res = s.isNumber(input);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": \"" << input << "\" "
                << res << std::endl;
    }
}