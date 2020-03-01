/**
 * Given two strings s and t , write a function to determine if t is an anagram of s.
 *
 * Example 1:
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 *
 * Example 2:
 * Input: s = "rat", t = "car"
 * Output: false
 *
 * Note:
 * You may assume the string contains only lowercase alphabets.
 * Follow up:
 * What if the inputs contain unicode characters? How would you adapt your solution to such case?
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    bool isAnagram(std::string s, std::string t) {
        auto ls = s.length(), lt = t.length();
        if (ls != lt) return false;
        std::unordered_map<char, int> smap, tmap;
        for (auto i = 0; i < ls; ++i) {
            smap[s[i]]++;
            tmap[t[i]]++;
        }
        if (smap.size() != tmap.size()) return false;
        for (const auto &sp : smap) {
            auto find = tmap.find(sp.first);
            if (!(find != tmap.end() && find->second == sp.second)) {
                return false;
            }
        }
        return true;
    }
};

struct Input {
    std::string s;
    std::string t;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{
        {"anagram", "nagaram"},
        {"rat", "car"}
    };

    for (auto &input : inputs) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.isAnagram(input.s, input.t) << std::endl;
    }
}