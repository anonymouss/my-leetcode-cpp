/**
 * Given a pattern and a string str, find if str follows the same pattern.
 *
 * Here follow means a full match, such that there is a bijection between a letter in pattern and a
 * non-empty word in str.
 *
 * Example 1:
 * Input: pattern = "abba", str = "dog cat cat dog"
 * Output: true
 *
 * Example 2:
 * Input:pattern = "abba", str = "dog cat cat fish"
 * Output: false
 *
 * Example 3:
 * Input: pattern = "aaaa", str = "dog cat cat dog"
 * Output: false
 *
 * Example 4:
 * Input: pattern = "abba", str = "dog dog dog dog"
 * Output: false
 *
 * Notes:
 * You may assume pattern contains only lowercase letters, and str contains lowercase letters that
 * may be separated by a single space.
 */

#include "MyMisc.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
public:
    bool wordPattern(std::string pattern, std::string str) {
        std::unordered_set<char> set;
        std::vector<char> unique_pattern;
        for (char c : pattern) {
            // remove duplicates but preserve order
            if (set.insert(c).second) { unique_pattern.emplace_back(c); }
        }
        std::size_t pattern_pos = 0;
        auto pattern_size = unique_pattern.size();

        std::unordered_map<std::string, char> mapper;
        std::string match;
        std::size_t start = 0, found = 0;
        while (found != std::string::npos) {
            found = str.find(' ', start);
            std::string substr = str.substr(start, found - start);
            if (mapper.find(substr) == mapper.end()) {
                if (pattern_pos >= pattern_size) { return false; }
                mapper[substr] = unique_pattern[pattern_pos++];
            }
            match += mapper[substr];
            start = found + 1;
        }
        // std::cout << match << " - " << pattern << std::endl;
        return match == pattern;
    }
};

struct Input {
    std::string pattern;
    std::string str;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{"abba", "dog cat cat dog"},
                              {"abba", "dog cat cat fish"},
                              {"aaaa", "dog cat cat dog"},
                              {"abba", "dog dog dog dog"}};

    for (auto &input : inputs) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.wordPattern(input.pattern, input.str) << std::endl;
    }
}