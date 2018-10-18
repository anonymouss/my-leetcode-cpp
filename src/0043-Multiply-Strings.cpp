/**
 * Given two non-negative integers num1 and num2 represented as strings, return
 * the product of num1 and num2, also represented as a string.
 *
 * Example 1:
 * Input: num1 = "2", num2 = "3"
 * Output: "6"
 *
 * Example 2:
 * Input: num1 = "123", num2 = "456"
 * Output: "56088"
 *
 * Note:
 * - The length of both num1 and num2 is < 110.
 * - Both num1 and num2 contain only digits 0-9.
 * - Both num1 and num2 do not contain any leading zero, except the number 0
 *   itself.
 * - You must not use any built-in BigInteger library or convert the inputs to
 *   integer directly.
 */

#include <iostream>
#include <string>

using std::string;

#define A2I(a) ((a) - '0')
#define I2A(i) ((i) + '0')

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1.empty() || num2.empty()) return "";
        string res(num1.length() + num2.length(), '0');
        for (int i = num1.length() - 1; i >= 0; --i) {
            for (int j = num2.length() - 1; j >= 0; --j) {
                int product = A2I(num1[i]) * A2I(num2[j]) + A2I(res[i + j + 1]);
                res[i + j + 1] = I2A(product % 10);
                res[i + j] = I2A(product / 10 + A2I(res[i + j]));
            }
        }
        auto pos = res.find_first_not_of('0');
        return pos == string::npos ? "0" : res.substr(pos);
    }
};

int main() {
    Solution s;
    int testId = 1;

    string num1_1{"2"}, num1_2{"3"};
    string num2_1{"123"}, num2_2{"456"};

    auto exeTest = [&](string &num1, string &num2) {
        auto res = s.multiply(num1, num2);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    };

    exeTest(num1_1, num1_2);
    exeTest(num2_1, num2_2);
}