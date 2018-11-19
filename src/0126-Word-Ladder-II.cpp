/**
 * Given two words (beginWord and endWord), and a dictionary's word list, find all shortest
 * transformation sequence(s) from beginWord to endWord, such that:
 * -1. Only one letter can be changed at a time
 * -2. Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
 * Note:
 * - Return an empty list if there is no such transformation sequence.
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
 * Output:
 * [
 *   ["hit","hot","dot","dog","cog"],
 *   ["hit","hot","lot","log","cog"]
 * ]
 *
 * Example 2:
 * Input:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log"]
 * Output: []
 * Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
 */

#include "../utils/MyMisc.h"
#include "../utils/MyContainerUtil.h"

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
using std:: swap;

// reference: https://leetcode.com/problems/word-ladder-ii/discuss/40591/The-fastest-C++-Solution-56ms!!
class Node;

using Ladder        = vector<string>;
using StringSet     = unordered_set<string>;
using NodeCompare   = bool(*)(Node *, Node *);
using NodeSet       = set<Node *, NodeCompare>;

class Node {
public:
    string mWord;
    vector<Node *> mParents;

    Node(string w) : mWord(w) {};

    void addParent(Node *parent) {
        mParents.emplace_back(parent);
    }

    // Yield all children of this node, and:
    //   1) If the child is found in $targetlayer, which means we found ladders that
    //      connect BEGIN-WORD and END-WORD, then we get all paths through this node
    //      to its ROOT node, and all paths through the target child node to its ROOT
    //      node, and combine the two group of paths to a group of ladders, and append
    //      these ladders to $ladders.
    //   2) Elif the $ladders is empty:
    //       2.1) If the child is found in $nextlayer, then get that child, and add
    //            this node to its parents.
    //       2.2) Else, add the child to nextlayer, and add this node to its parents.
    //   3) Else, do nothing.
    void yeildChildren(NodeSet &nextLayer, StringSet &wordList, NodeSet &targetLayer,
            vector<Ladder> &ladders, bool forward) {
        auto nextWord = mWord;
        for (int i = 0, n = nextWord.length(); i < n; ++i) {
            char originalChar = nextWord[i];
            for (nextWord[i] = 'a'; nextWord[i] <= 'z'; ++nextWord[i]) {
                if (wordList.count(nextWord)) {
                    auto *pChild = new Node(nextWord);
                    yeildOneChild(pChild, nextLayer, targetLayer, ladders, forward);
                }
            }
            nextWord[i] = originalChar; // restore
        }
    }

    void yeildOneChild(Node *child, NodeSet &nextLayer, NodeSet &targetLayer,
            vector<Ladder> &ladders, bool forward) {
        auto childItr = targetLayer.find(child);
        if (childItr != targetLayer.end()) {
            for (auto thisLadders : this->getLadders()) {
                for (auto thatLadders : (*childItr)->getLadders()) {
                    if (forward) {
                        ladders.emplace_back(thisLadders);
                        ladders.back().insert(ladders.back().end(),
                                thatLadders.rbegin(), thatLadders.rend());
                    } else {
                        ladders.emplace_back(thatLadders);
                        ladders.back().insert(ladders.back().end(),
                                thisLadders.rbegin(), thisLadders.rend());
                    }
                }
            }
        } else if (ladders.empty()) {
            auto childNextItr = nextLayer.find(child);
            if (childNextItr != nextLayer.end()) {
                (*childNextItr)->addParent(this);
            } else {
                child->addParent(this);
                nextLayer.emplace(child);
            }
        }
    }

    vector<Ladder> getLadders() {
        vector<Ladder> ladders;
        if (mParents.empty()) {
            ladders.emplace_back(Ladder(1, mWord));
        } else {
            for (auto *parent : mParents) {
                for (auto ladder : parent->getLadders()) {
                    ladders.emplace_back(ladder);
                    ladders.back().emplace_back(mWord);
                }
            }
        }
        return ladders;
    }
};

bool nodeCompare(Node *pNodeA, Node *pNodeB) {
    return pNodeA->mWord < pNodeB->mWord;
}

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<Ladder> ladders;

        // if endWord doesn't exist in wordList, obviously there is no valid ladder
        bool exist = false;
        for (const auto &w : wordList) {
            if (w == endWord) {
                exist = true;
                break;
            }
        }
        if (!exist) return ladders;

        Node head(beginWord), tail(endWord);
        NodeSet frontLayer(nodeCompare), backLayer(nodeCompare);
        NodeSet *pLayerA = &frontLayer, *pLayerB = &backLayer;
        StringSet wordListSet(wordList.begin(), wordList.end());
        bool forward = true;

        frontLayer.emplace(&head);
        backLayer.emplace(&tail);
        while (!pLayerA->empty() && !pLayerB->empty() && ladders.empty()) {
            NodeSet nextLayer(nodeCompare); // clear everytime
            if (pLayerA->size() > pLayerB->size()) {
                swap(pLayerA, pLayerB);
                forward = !forward;
            }
            for (auto *node : *pLayerA) {
                wordListSet.erase(node->mWord);
            }
            for (auto *node : *pLayerA) {
                node->yeildChildren(nextLayer, wordListSet, *pLayerB, ladders, forward);
            }
            swap(*pLayerA, nextLayer);
        }
        return ladders;
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
        auto res = s.findLadders(beginWirds[i], endWords[i], wordLists[i]);
        myDispVector2D(res);
    }
}