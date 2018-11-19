/**
 * Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest
 * transformation sequence from beginWord to endWord, such that:
 * - Only one letter can be changed at a time.
 * - Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
 *
 * Note:
 * - Return 0 if there is no such transformation sequence.
 * - All words have the same length.
 * - All words contain only lowercase alphabetic characters.
 * - You may assume no duplicates in the word list.
 * - You may assume beginWord and endWord are non-empty and are not the same.
 *
 * Example 1:
 * Input:
 * beginWord = "hit",
 * endWord = "cog",
 * wordList = ["hot","dot","dog","lot","log","cog"]
 * Output: 5
 * Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
 * return its length 5.
 *
 * Example 2:
 * Input:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log"]
 * Output: 0
 * Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
 */

#include "../utils/MyMisc.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <algorithm>

using std::vector;
using std::string;
using std::unordered_set;
using std::set;

bool comp(string s1, string s2) {
    return s1 < s2;
}

using Set = set<string, bool (*)(string, string)>;
using StrSet = unordered_set<string>;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // if endWord doesn't exist in wordList, obviously there is no valid ladder
        bool exist = false;
        for (const auto &w : wordList) {
            if (w == endWord) {
                exist = true;
                break;
            }
        }
        if (!exist) return 0;

        Set set1(comp), set2(comp);
        StrSet wordListSet(wordList.begin(), wordList.end());
        set1.emplace(beginWord);
        set2.emplace(endWord);

        wordListSet.erase(beginWord);
        wordListSet.erase(endWord);

        return minLadderLength(set1, set2, wordListSet, 2);
    }

    int minLadderLength(Set &set1, Set &set2, StrSet &wordList, int length) {
        if(set1.empty()) return 0;
        Set newSet(comp);
        for (auto s : set1) {
            for (int i = 0, n = s.length(); i < n; ++i) {
                char originalChar = s[i];
                for (s[i] = 'a'; s[i] <= 'z'; ++s[i]) {
                    if (set2.find(s) != set2.end()) return length;
                    if (wordList.count(s)) {
                        newSet.insert(s);
                        wordList.erase(s);
                    }
                }
                s[i] = originalChar;
            }
        }
        if (newSet.size() < set2.size()) {
            return minLadderLength(newSet, set2, wordList, length + 1);
        } else {
            return minLadderLength(set2, newSet, wordList, length + 1);
        }
    }
};

int main() {
    Solution s;
    vector<string> beginWirds{"hit", "hit"};
    vector<string> endWords{"cog", "cog"};
    vector<vector<string>> wordLists{
        {"hot", "dot", "dog", "lot", "log", "cog"},
        {"hot", "dot", "dog", "lot", "log"}
    };

    if (beginWirds.size() != endWords.size() || beginWirds.size() != wordLists.size()) {
        std::cout << "incorrect test cases\n";
        return -1;
    }

    for (int i = 0; i < beginWirds.size(); ++i) {
        TestCount();
        auto res = s.ladderLength(beginWirds[i], endWords[i], wordLists[i]);
        std::cout << res << std::endl;
    }
}