/* 请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

示例 1：
输入：s = "We are happy."
输出："We%20are%20happy."

限制：
0 <= s 的长度 <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <string>
#include <iostream>

class Solution {
public:
    std::string replaceSpace(std::string s) {
        std::string res;
        for (const auto &c : s) {
            if (c == ' ') {
                res.push_back('%');
                res.push_back('2');
                res.push_back('0');
            } else {
                res.push_back(c);
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    std::cout << s.replaceSpace("We are happy") << std::endl;
}