/**
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
 * (you may want to display this pattern in a fixed font for better legibility)
 *
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR"
 *
 * Write the code that will take a string and make this conversion given a number of rows:
 *
 * string convert(string s, int numRows);
 * 
 * Example 1:
 * Input: s = "PAYPALISHIRING", numRows = 3
 * Output: "PAHNAPLSIIGYIR"
 * 
 * Example 2:
 * Input: s = "PAYPALISHIRING", numRows = 4
 * Output: "PINALSIGYAHRPI"
 * Explanation:
 *
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

# define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
#define ASSERT if (index >= len) break;

class Solution {
public:
    string convert(string s, int numRows) {
        if (s.empty() || numRows == 1) return s;
        string res{""};
        auto len = s.length();
        int gap = 2 * (numRows - 1);
        int lgap = gap, rgap = 0, index = 0;
        for (int r = 0; r < numRows; ++r) {
            index = r;
            res += s[r];
            while (true) {
                if (lgap > 0) {
                    index += lgap;
                    ASSERT
                    res += s[index];
                }
                if (rgap > 0) {
                    index += rgap;
                    ASSERT
                    res += s[index];
                }
            }
            lgap -= 2;
            rgap += 2;
        }
        return res;
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    string convert(string s, int numRows) {
        if (s.empty() || numRows == 1) return s;
        int len = s.length();
        int rows = (len < numRows) ? len : numRows;
        bool goingDown = false;
        vector<string> strRows(rows);
        int curRow = 0;
        for (char c : s) {
            strRows[curRow] += c;
            if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
            curRow += (goingDown ? 1 : -1);
        }
        string res;
        for (string row : strRows) res += row;
        return res;
    }
};
#endif

int main() {
    Solution s;
    string str{"PAYPALISHIRING"};

    std::cout << "Case 1: " << s.convert(str, 3) << std::endl;
    std::cout << "Case 2: " << s.convert(str, 4) << std::endl;
}