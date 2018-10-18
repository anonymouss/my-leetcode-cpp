/**
 * Given an array of strings, group anagrams together.
 *
 * Example:
 * Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
 * Output:
 * [
 *   ["ate","eat","tea"],
 *   ["nat","tan"],
 *   ["bat"]
 * ]
 *
 * Note:
 * - All inputs will be in lowercase.
 * - The order of your output does not matter.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using std::vector;
using std::string;
using std::unordered_map;
using std::sort;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> map;
        for (auto &str : strs) {
            auto s = str;
            sort(s.begin(), s.end());
            auto it = map.find(s);
            if (it == map.end()) {
                map.emplace(s, vector<string>{str});
            } else {
                it->second.emplace_back(str);
            }
        }
        for (auto &m : map) {
            res.emplace_back(m.second);
        }
        return res;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<string>> inputStr{
        {"eat", "tea", "tan", "ate", "nat", "bat"}
    };

    for (auto &str : inputStr) {
        auto res = s.groupAnagrams(str);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (auto &v : res) {
            std::cout << "    [";
            for (auto &s : v) {
                std::cout << "\"" << s << "\", ";
            }
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    }
}