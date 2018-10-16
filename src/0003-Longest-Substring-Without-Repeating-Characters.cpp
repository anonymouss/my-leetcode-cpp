/**
 * Given a string, find the length of the longest substring without repeating
 * characters.
 *
 * Example 1:
 *
 * Input: "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 *
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 *
 * Input: "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 * Note that the answer must be a substring, "pwke" is a subsequence and not a
 * substring.
 */

#include <iostream>
#include <string>
#include <array>

using std::string;
using std::array;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        auto position = array<int, 256>{-1};
        position.fill(-1);
        int longest = 0;
        int lastRepeatPos = -1;
        auto length = s.length();
        for (auto i = 0; i < length; ++i) {
            auto ch = s[i];
            lastRepeatPos = position[ch] > lastRepeatPos ? position[ch]
                                                        : lastRepeatPos;
            longest = i - lastRepeatPos > longest ? i - lastRepeatPos : longest;
            position[ch] = i;
        }
        return longest;
    }
};

int main() {
    Solution s;

    string s1{"abcabcbb"};
    string s2{"bbbbb"};
    string s3{"pwwkew"};

    std::cout << "Case 1 : " << s.lengthOfLongestSubstring(s1) << std::endl;
    std::cout << "Case 2 : " << s.lengthOfLongestSubstring(s2) << std::endl;
    std::cout << "Case 3 : " << s.lengthOfLongestSubstring(s3) << std::endl;
}