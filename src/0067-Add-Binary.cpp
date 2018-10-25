/**
 * Given two binary strings, return their sum (also a binary string).
 * The input strings are both non-empty and contains only characters 1 or 0.
 *
 * Example 1:
 * Input: a = "11", b = "1"
 * Output: "100"
 *
 * Example 2:
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    string addBinary(string a, string b) {
        int ia = a.length() - 1, ib = b.length() - 1;
        string res{""};
        int va = 0, vb = 0, vc = 0;
        while (ia >= 0 || ib >= 0) {
            if (ia >= 0 && ib >=0) {
                va = a[ia] - '0';
                vb = b[ib] - '0';
            } else if (ia < 0) {
                va = 0;
                vb = b[ib] - '0';
            } else if (ib < 0) {
                vb = 0;
                va = a[ia] - '0';
            }
            int sum = va + vb + vc;
            res = static_cast<char>(sum % 2 + '0') + res;
            vc = sum / 2;
            --ia; --ib;
        }
        if (vc == 1) res = '1' + res;
        return res;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<string>> inputs{
        // a, b
        {"11", "1"},
        {"1010", "1011"}
    };

    for (auto &input : inputs) {
        auto res = s.addBinary(input[0], input[1]);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}