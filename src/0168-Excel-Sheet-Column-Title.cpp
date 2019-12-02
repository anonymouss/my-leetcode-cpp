/**
 * Given a positive integer, return its corresponding column title as appear in an Excel sheet.
 * For example:
 *     1 -> A
 *     2 -> B
 *     3 -> C
 *     ...
 *     26 -> Z
 *     27 -> AA
 *     28 -> AB 
 *     ...
 * 
 * Example 1:
 * Input: 1
 * Output: "A"
 * 
 * Example 2:
 * Input: 28
 * Output: "AB"
 * 
 * Example 3:
 * Input: 701
 * Output: "ZY"
 */

#include "MyMisc.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string convertToTitle(int n) {
        std::string title = "";
        while (n > 0) {
            --n;
            char t = 'A' + n % 26;
            title += t;
            n /= 26;
        }
        std::reverse(title.begin(), title.end());
        return title;
    }
};

int main() {
    Solution sln;
    std::vector<int> inputs{1, 28, 701, 26, 52};
    for (auto &n : inputs) {
        TestCount();
        std::cout << sln.convertToTitle(n) << std::endl;
    }
}