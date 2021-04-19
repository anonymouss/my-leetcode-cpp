/* 请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

提示：
s.length <= 40000
注意：本题与主站 3 题相同：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        int max_len = 0;
        int start = 0, cur = 0;
        std::unordered_set<char> hash;
        for (; cur < s.length(); ++cur) {
            if (hash.count(s[cur])) {
                for (auto i = start; i < cur; ++i) {
                    if (s[i] == s[cur]) {
                        start = i + 1;
                        hash.erase(hash.find(s[cur]));
                        break;
                    }
                }
            }
            hash.emplace(s[cur]);
            auto len = cur - start + 1;
            max_len = len > max_len ? len : max_len;
        }
        return max_len;
    }
};

int main() {
    Solution s;
    std::vector<std::string> strs{
        "abcabcbb",
        "bbbbb",
        "pwwkew"
    };

    for (const auto &str : strs) {
        std::cout << s.lengthOfLongestSubstring(str) << std::endl;
    }
}