/* 
给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25
翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

示例 1:
输入: 12258
输出: 5
解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"

提示：
0 <= num < 231 */

#include <iostream>
#include <vector>

class Solution {
public:
    int translateNum(int num) {
        if (num < 10) return 1;
        auto v = num % 100;
        if (v < 26 && v > 9) {
            // 两位数
            return translateNum(num / 10) + translateNum(num / 100);
        } else {
            // 只有一位数
            return translateNum(num / 10);
        }
    }
};

int main() {
    Solution s;

    std::vector<int> ns{12258};
    for (const auto &n : ns) {
        std::cout << s.translateNum(n) << std::endl;
    }
}