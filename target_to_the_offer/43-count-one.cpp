/* 输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。
例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。

示例 1：
输入：n = 12
输出：5

示例 2：
输入：n = 13
输出：6

限制：
1 <= n < 2^31
注意：本题与主站 233 题相同：https://leetcode-cn.com/problems/number-of-digit-one/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>

class Solution {
public:
    int countDigitOne(int n) {
        long base = 1;
        int high = n / 10, cur = n % 10, low = 0, res = 0;
        while (high != 0 || cur != 0) {
            if (cur == 0) res += high * base;
            else if (cur == 1) res += high * base + low + 1;
            else res += (high + 1) * base;
            low += cur * base;
            cur = high % 10;
            high = high / 10;
            base *= 10;
        }
        return res;
    }
};

int main() {
    Solution s;

    std::vector<int> ns{12, 13};
    for (const auto &n : ns) {
        std::cout << s.countDigitOne(n) << std::endl;
    }
}