/**
 * Design a data structure that supports the following two operations:
 * void addWord(word)
 * bool search(word)
 * search(word) can search a literal word or a regular expression string containing only letters a-z
 * or .. A . means it can represent any one letter.
 *
 * Example:
 * addWord("bad")
 * addWord("dad")
 * addWord("mad")
 * search("pad") -> false
 * search("bad") -> true
 * search(".ad") -> true
 * search("b..") -> true
 * Note:
 * You may assume that all words are consist of lowercase letters a-z.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        mIsEnd = false;
        links = std::vector<WordDictionary *>(26, nullptr);
    }
    
    /** Adds a word into the data structure. */
    void addWord(std::string word) {
        auto *cur = this;
        for (auto &w : word) {
            if (cur->links[w - 'a'] == nullptr) {
                cur->links[w - 'a'] = new WordDictionary();
            }
            cur = cur->links[w - 'a'];
        }
        cur->mIsEnd = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to
     * represent any one letter. */
    bool search(std::string word) {
        return search_l(word.begin(), word.end(), this);
    }

private:
    bool mIsEnd;
    std::vector<WordDictionary *> links;

    using T = std::string::iterator;
    bool search_l(T first, T last, WordDictionary *node) {
        if (first == last) {
            return node->mIsEnd;
        } else if ((*first) == '.') {
            for (auto *link : node->links) {
                if (link && search_l(first + 1, last, link)) {
                    return true;
                }
            }
        } else if (node->links[(*first) - 'a'] != nullptr) {
            return search_l(first + 1, last, node->links[(*first) - 'a']);
        }
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

int main() {
    WordDictionary wd;
    wd.addWord("bad");
    wd.addWord("dad");
    wd.addWord("mad");
    assert(wd.search("pad") == false);
    assert(wd.search("bad") == true);
    assert(wd.search(".ad") == true);
    assert(wd.search("b..") == true);
    std::cout << "OK, done!" << std::endl;
}