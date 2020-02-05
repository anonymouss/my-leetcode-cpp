/**
 * All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example:
 * "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the
 * DNA.
 * Write a function to find all the 10-letter-long sequences (substrings) that occur more than once
 * in a DNA molecule.
 *
 * Example:
 * Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 * Output: ["AAAAACCCCC", "CCCCCAAAAA"]
 */

#include "MyMisc.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

class Solution {
public:
    std::vector<std::string> findRepeatedDnaSequences(std::string s) {
        auto length = s.length();
        if (length < 10) return {};
        std::unordered_set<int> hashSet;
        std::unordered_set<std::string> result; // avoid duplicates
        int key = 0;
        for (auto i = 0; i < 10; ++i) {
            key &= 0x7ffffff;
            key <<= 3;
            key |= (s[i] & 7);
        }
        hashSet.emplace(key);
        for (auto i = 10; i < length; ++i) {
            key &= 0x7ffffff;
            key <<= 3;
            key |= (s[i] & 7);
            if (hashSet.count(key) == 1) { // contains from C++20
                result.emplace(s.substr(i - 9, 10));
            } else {
                hashSet.emplace(key);
            }
        }
        std::vector<std::string> realResult;
        for (const auto &r : result) realResult.emplace_back(r);
        return realResult;
    }
};

int main() {
    Solution sln;
    std::vector<std::string> sv{"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT", "AAAAAAAAAAAA", "GAGAGAGAGAG"};

    auto print_sv = [](const std::vector<std::string> &sv) {
        std::cout << "[";
        for (const auto &s : sv) {
            std::cout << "\"" << s << "\", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &s : sv) {
        TestCount();
        print_sv(sln.findRepeatedDnaSequences(s));
    }
}
