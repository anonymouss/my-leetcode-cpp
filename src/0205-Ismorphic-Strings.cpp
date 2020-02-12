/**
 * Given two strings s and t, determine if they are isomorphic.
 * Two strings are isomorphic if the characters in s can be replaced to get t.
 * All occurrences of a character must be replaced with another character while preserving the order
 * of characters. No two characters may map to the same character but a character may map to itself.
 *
 * Example 1:
 * Input: s = "egg", t = "add"
 * Output: true
 *
 * Example 2:
 * Input: s = "foo", t = "bar"
 * Output: false
 *
 * Example 3:
 * Input: s = "paper", t = "title"
 * Output: true
 *
 * Note: You may assume both s and t have the same length.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    bool isIsomorphic(std::string s, std::string t) {
        auto ls = s.length(), lt = t.length();
        if (ls != lt) return false;
        std::unordered_map<char, char> maps2t;
        std::unordered_map<char, char> mapt2s;
        for (auto i = 0; i < ls; ++ i) {
            auto its2t = maps2t.find(s[i]);
            auto itt2s = mapt2s.find(t[i]);
            if (its2t == maps2t.end() && itt2s == mapt2s.end()) {
                maps2t[s[i]] = t[i];
                mapt2s[t[i]] = s[i];
            } else if (its2t != maps2t.end() && itt2s != mapt2s.end()) {
                if (its2t->second != t[i] || itt2s->second != s[i]) {
                    return false;
                } // else --> may true, ok till now, continue
            } else {
                return false;
            }
        }
        return true;
    }
};

struct Input {
    std::string s;
    std::string t;
    Input(std::string _s, std::string _t) : s(_s), t(_t) {}
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{"egg", "add"}, {"foo", "bar"}, {"paper", "title"}, {"ab", "aa"}};

    for (auto &input : inputs) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.isIsomorphic(input.s, input.t) << std::endl;
    }
}