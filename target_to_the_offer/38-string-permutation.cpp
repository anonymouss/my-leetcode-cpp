/* 输入一个字符串，打印出该字符串中字符的所有排列。
你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

示例:
输入：s = "abc"
输出：["abc","acb","bac","bca","cab","cba"]

限制：
1 <= s 的长度 <= 8

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    std::vector<std::string> permutation(std::string s) {
        std::vector<std::string> res;
        dfs(&res, s, 0);
        return res;
    }

private:
    void dfs(std::vector<std::string> *res, std::string &s, int i) {
        if (i == s.size() - 1) {
            res->emplace_back(s);
            return;
        }
        std::unordered_set<char> set;
        for (auto j = i; j < s.size(); ++j) {
            if (set.count(s[j])) continue;
            set.emplace(s[j]);
            std::swap(s[i], s[j]);
            dfs(res, s, i + 1);
            std::swap(s[i], s[j]);
        }
    }
};

int main() {
    Solution sl;

    auto print_vs = [](const std::vector<std::string> &vs) {
        for (const auto &s : vs) std::cout << s << ", ";
        std::cout << std::endl;
    };

    std::vector<std::string> ss{"abc"};
    for (const auto &s : ss) {
        print_vs(sl.permutation(s));
    }
}