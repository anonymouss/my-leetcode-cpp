/**
 * Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return
 * the length of last word in the string.
 *
 * If the last word does not exist, return 0.
 *
 * Note: A word is defined as a character sequence consists of non-space characters only.
 *
 * Example:
 * Input: "Hello World"
 * Output: 5
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int cnt = 0, i = s.length() - 1;
        while (i >= 0 && s[i] == ' ') --i;
        for (; i >= 0 && s[i] != ' '; --i)
            ++cnt;
        return cnt;
    }
};

int main() {
    Solution solution;
    int testId = 1;

    vector<string> ss{
        "Hello World",
        "",
        "a "
    };

    for (auto &s : ss) {
        auto res = solution.lengthOfLastWord(s);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}