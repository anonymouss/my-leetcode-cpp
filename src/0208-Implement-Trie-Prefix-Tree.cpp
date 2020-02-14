/**
 * Implement a trie with insert, search, and startsWith methods.
 *
 * Example:
 * Trie trie = new Trie();
 *
 * trie.insert("apple");
 * trie.search("apple");   // returns true
 * trie.search("app");     // returns false
 * trie.startsWith("app"); // returns true
 * trie.insert("app");   
 * trie.search("app");     // returns true
 *
 * Note:
 * You may assume that all inputs are consist of lowercase letters a-z.
 * All inputs are guaranteed to be non-empty strings.
 */

#include "MyMisc.h"

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    virtual ~Trie() {
        delete root;
    }

    /** Inserts a word into the trie. */
    void insert(std::string word) {
        auto *node = root;
        for (auto i = 0; i < word.length(); ++i) {
            auto curChar = word[i];
            if (!node->containsKey(curChar)) {
                node->put(curChar, new TrieNode());
            }
            node = node->get(curChar);
        }
        node->setEnd();
    }
    
    /** Returns if the word is in the trie. */
    bool search(std::string word) {
        auto *node = searchPrefix(word);
        return (node != nullptr) && (node->isEnd());
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix) {
        auto *node = searchPrefix(prefix);
        return node != nullptr;
    }

private:
    struct TrieNode {
        std::vector<TrieNode *> links;
        bool mIsEnd;

        TrieNode() {
            links = std::vector<TrieNode *>(26, nullptr);
            mIsEnd = false;
        }

        virtual ~TrieNode() {
            for (auto *node : links) {
                delete node;
            }
        }

        bool containsKey(char ch) {
            return links[ch - 'a'] != nullptr;
        }

        TrieNode *get(char ch) {
            return links[ch - 'a'];
        }

        void put(char ch, TrieNode *node) {
            links[ch - 'a'] = node;
        }

        void setEnd() {
            mIsEnd = true;
        }

        bool isEnd() const {
            return mIsEnd;
        }
    };

    TrieNode *root;
    TrieNode *searchPrefix(std::string word) {
        auto *node = root;
        for (auto i = 0; i < word.length(); ++i) {
            auto curChar = word[i];
            if (node->containsKey(curChar)) {
                node = node->get(curChar);
            } else {
                return nullptr;
            }
        }
        return node;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main() {
    auto *trie = new Trie();

    trie->insert("apple");
    assert(trie->search("apple") == true);
    assert(trie->search("app") == false);
    assert(trie->startsWith("app") == true);
    trie->insert("app");
    assert(trie->search("app") == true);

    std::cout << "OK, done!" << std::endl;
}