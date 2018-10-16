/**
 * You are given a string, s, and a list of words, words, that are all of the
 * same length. Find all starting indices of substring(s) in s that is a
 * concatenation of each word in words exactly once and without any intervening
 * characters.
 *
 * Example 1:
 * Input:
 *   s = "barfoothefoobarman",
 *   words = ["foo","bar"]
 * Output: [0,9]
 * Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar"
 * respectively. The output order does not matter, returning [9,0] is fine too.
 *
 * Example 2:
 * Input:
 *   s = "wordgoodstudentgoodword",
 *   words = ["word","student"]
 * Output: []
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (s.empty() || words.empty()) return res;

        unordered_map<string, int> wordCount;
        auto wordLength = words[0].length(), sLength = s.length();
        auto windowSize = words.size() * wordLength;
        for (const auto &word : words) {
            // elements in words must have the same length
            if (word.length() != wordLength) return res;
            wordCount[word]++;
        }

        for (auto round = 0; round < wordLength; ++round) {
            unordered_map<string, int> windowMap;
            int curWindowCounts = 0, curStartPos = round;
            for (auto i = curStartPos, j = curStartPos;
                    j  + wordLength <= s.length();
                    j += wordLength) {
                auto substring = s.substr(j, wordLength);
                if (wordCount.find(substring) != wordCount.end()) {
                    if (windowMap[substring] < wordCount[substring]) {
                        windowMap[substring]++;
                        curWindowCounts++;
                    } else {
                        // discard all words before the abnormal duplicated word
                        // (till the first repeating one is skipped)
                        while (true) {
                            auto w = s.substr(curStartPos, wordLength);
                            curStartPos += wordLength;
                            if (w == substring)
                                break;
                            windowMap[w]--;
                            curWindowCounts--;
                        }
                    }

                    // find a match, save result and discard first word, continue
                    if (curWindowCounts == words.size()) {
                        res.emplace_back(curStartPos);
                        auto w = s.substr(curStartPos, wordLength);
                        windowMap[w]--;
                        curWindowCounts--;
                        curStartPos += wordLength;
                    }
                } else {
                    // skip to the one after abnormal word
                    curStartPos = j + wordLength;
                    windowMap.clear();
                    curWindowCounts = 0;
                }
            }
        }
        return res;
    }
};

int main() {
    Solution slution;
    static int testId = 1;

    string s1{"barfoothefoobarman"};
    vector<string> words1{"foo","bar"};

    string s2{"wordgoodstudentgoodword"};
    vector<string> words2{"word","student"};

    string s3{"wordgoodgoodgoodbestword"};
    vector<string> words3{"word","good","best","word"};

    auto exeTest = [&](string &s, vector<string> &words) {
        std::cout << "Case " << testId << ": [";
        vector<int> res = slution.findSubstring(s, words);
        for (const auto &v : res)
            std::cout << v << ", ";
        std::cout << "]" << std::endl;
        ++testId;
    };

    exeTest(s1, words1);
    exeTest(s2, words2);
    exeTest(s3, words3);
}