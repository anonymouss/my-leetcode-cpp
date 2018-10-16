/**
 * Write a function to find the longest common prefix string amongst an array of
 * strings. If there is no common prefix, return an empty string "".
 *
 * Example 1:
 * Input: ["flower","flow","flight"]
 * Output: "fl"
 *
 * Example 2:
 * Input: ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 *
 * Note: All given inputs are in lowercase letters a-z.
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        int vecNum = strs.size(), idx = 0;
        if (vecNum == 1) return strs[0];
        string res{""};
        int minLen = INT32_MAX;
        for (int i = 0; i < vecNum; ++i) minLen = MIN(minLen, strs[i].length());
        bool CONTINUE = true;
        while (CONTINUE) {
            int i = 0;
            for (; i < vecNum && idx < strs[i].length(); ++i) {
                if (strs[0][idx] != strs[i][idx]) {
                    CONTINUE = false;
                    break;
                }
            }
            if (idx == minLen) CONTINUE = false;
            if (i == vecNum) res += strs[0][idx];
            ++idx; 
        }        
        return res;
    }
};

int main() {
    Solution s;

    vector<string> strs1{"flower", "flow", "flight"};
    vector<string> strs2{"dog", "racecar", "car"};
    vector<string> strs3;
    vector<string> strs4{"", ""};

    std::cout << "Case 1: " << s.longestCommonPrefix(strs1) << std::endl;
    std::cout << "Case 2: " << s.longestCommonPrefix(strs2) << std::endl;
    std::cout << "Case 3: " << s.longestCommonPrefix(strs3) << std::endl;
    std::cout << "Case 4: " << s.longestCommonPrefix(strs4) << std::endl;
}