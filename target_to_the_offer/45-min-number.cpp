/* 输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

示例 1:
输入: [10,2]
输出: "102"

示例 2:
输入: [3,30,34,5,9]
输出: "3033459"

提示:
0 < nums.length <= 100
说明:

输出结果可能非常大，所以你需要返回一个字符串而不是整数
拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0
通过次数65,939提交次数117,747

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string minNumber(std::vector<int> &nums) {
        std::vector<std::string> numstrs;
        for (const auto &n : nums) numstrs.emplace_back(std::to_string(n));
        std::sort(numstrs.begin(), numstrs.end(),
                [](const std::string &a, const std::string &b) {
                    return (a + b) < (b + a);
                });
        std::string res;
        for (const auto &s : numstrs) res += s;
        return res;
    }
};

int main() {
    Solution s;
    std::vector<std::vector<int>> ns{
        {10, 2},
        {3, 30, 34, 5, 9}
    };

    for (auto &n : ns) {
        std::cout << s.minNumber(n) << std::endl;
    }
}