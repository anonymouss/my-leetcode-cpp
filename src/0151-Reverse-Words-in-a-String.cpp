/**
 * Given an input string, reverse the string word by word.
 * Example 1:
 * Input: "the sky is blue"
 * Output: "blue is sky the"
 * Example 2:
 * Input: "  hello world!  "
 * Output: "world! hello"
 * Explanation: Your reversed string should not contain leading or trailing spaces.
 * Example 3:
 * Input: "a good   example"
 * Output: "example good a"
 * Explanation: You need to reduce multiple spaces between two words to a single space in the
 * reversed string.
 * Note:
 * A word is defined as a sequence of non-space characters.
 * Input string may contain leading or trailing spaces. However, your reversed string should not
 * contain leading or trailing spaces.
 * You need to reduce multiple spaces between two words to a single space in the reversed string.
 * Follow up:
 * For C programmers, try to solve it in-place in O(1) extra space.
 */

#include "MyMisc.h"

#include <string>
#include <vector>

class Solution {
public:
    std::string reverseWords(std::string s) {
        std::vector<std::string> words;
        std::string word{};
        for (auto i = 0; i < s.length(); ++i) {
            if (s[i] == ' ') {
                if (!word.empty()) {
                    words.emplace_back(word);
                    word.clear();
                }
                continue;
            }
            word += s[i];
        }
        if (!word.empty()) words.emplace_back(word);
        if (words.empty()) return "";
        std::string res = "";
        for (auto i = words.size() - 1; i > 0; i--) {
            res = res + words[i] + " ";
        }
        return res + words[0];
    }
};

int main() {
    Solution s;

    std::vector<std::string> inputs {
        "the sky is blue",
        "  hello world!  ",
        "a good   example"
    };

    for (auto &input : inputs) {
        TestCount();
        std::cout << s.reverseWords(input) << std::endl;
    }
}