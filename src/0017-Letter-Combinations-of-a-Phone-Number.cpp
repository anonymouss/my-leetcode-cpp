/**
 * Given a string containing digits from 2-9 inclusive, return all possible
 * letter combinations that the number could represent.
 *
 * A mapping of digit to letters (just like on the telephone buttons) is given
 * below.
 * Note that 1 does not map to any letters.
 *
 *   1 (o_o)   2 (abc)   3 (def)
 *   4 (ghi)   5 (jkl)   6 (mno)
 *   7(pqrs)   8 (tuv)   9(wxyz)
 *    *(+)      0(_)      #(^)
 *
 * Example:
 * Input: "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 *
 * Note: Although the above answer is in lexicographical order, your answer
 * could be in any order you want.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <utility>

using std::vector;
using std::string;
using std::stack;
using std::pair;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        int layer = -1, lastLayer = layer, maxLayer = digits.length();
        if (maxLayer == 0) return res;
        // dfs
        stack<pair<char, int>> stk; stk.push({'?', layer});
        string s{""};
        while (!stk.empty()) {
            auto t = stk.top();
            auto ch = t.first;
            layer = t.second;
            // back to upper layer
            for (auto i = layer; i < lastLayer; ++i) s.pop_back();
            lastLayer = layer;
            if (ch != '?') s.push_back(ch);
            if (layer == maxLayer - 1) {
                res.insert(res.begin(), s);
                s.pop_back();
            }
            stk.pop();
            if (layer < maxLayer - 1) {
                ++layer;
                auto str = digitToStr(digits[layer]);
                for (const auto &ch : str) {
                    stk.push({ch, layer});
                }
            }
        }
        return res;
    }

    string digitToStr(const char &ch) {
        switch(ch) {
            case '2': return "abc";
            case '3': return "def";
            case '4': return "ghi";
            case '5': return "jkl";
            case '6': return "mno";
            case '7': return "pqrs";
            case '8': return "tuv";
            case '9': return "wxyz";
            default: return "";
        }
    }
};

int main() {
    Solution s;

    string input1{"23"};
    string input2{"234"};
    string input3{""};

    auto exeTest = [&](string &input, int testId) {
        auto res = s.letterCombinations(input);
        std::cout << "Case " << testId << ":" << " [";
        for (const auto &s : res) {
            std::cout << "\"" << s << "\", ";
        }
        std::cout << "]\n";
    };

    exeTest(input1, 1);
    exeTest(input2, 2);
    exeTest(input3, 3);
}