/**
 * Given an array of words and a width maxWidth, format the text such that each line has exactly
 * maxWidth characters and is fully (left and right) justified.
 * You should pack your words in a greedy approach; that is, pack as many words as you can in each
 * line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
 * Extra spaces between words should be distributed as evenly as possible. If the number of spaces
 * on a line do not divide evenly between words, the empty slots on the left will be assigned more
 * spaces than the slots on the right.
 * For the last line of text, it should be left justified and no extra space is inserted between words.
 *
 * Note:
 * A word is defined as a character sequence consisting of non-space characters only.
 * Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
 * The input array words contains at least one word.
 *
 * Example 1:
 * Input:
 * words = ["This", "is", "an", "example", "of", "text", "justification."]
 * maxWidth = 16
 * Output:
 * [
 *    "This    is    an",
 *    "example  of text",
 *    "justification.  "
 * ]
 *
 * Example 2:
 * Input:
 * words = ["What","must","be","acknowledgment","shall","be"]
 * maxWidth = 16
 * Output:
 * [
 *   "What   must   be",
 *   "acknowledgment  ",
 *   "shall be        "
 * ]
 * Explanation: Note that the last line is "shall be    " instead of "shall     be",
 *              because the last line must be left-justified instead of fully-justified.
 *              Note that the second line is also left-justified becase it contains only one word.
 *
 * Example 3:
 * Input:
 * words = ["Science","is","what","we","understand","well","enough","to","explain",
 *          "to","a","computer.","Art","is","everything","else","we","do"]
 * maxWidth = 20
 * Output:
 * [
 *   "Science  is  what we",
 *   "understand      well",
 *   "enough to explain to",
 *   "a  computer.  Art is",
 *   "everything  else  we",
 *   "do                  "
 * ]
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        vector<string> line;
        string lineStr{""};
        int count = 0;
        for (int i = 0; i < words.size(); ++i) {
            if (count + words[i].length() + line.size() > maxWidth) {
                int totalSpaces = maxWidth - count;
                if (line.size() > 1) {
                    int averageSpaces = totalSpaces / (line.size() - 1);
                    int remainingSpaces = totalSpaces % (line.size() - 1);
                    string spaces(averageSpaces, ' ');
                    for (int i = 0; i < line.size(); ++i) {
                        lineStr += line[i];
                        if (i != line.size() - 1) lineStr += string(averageSpaces, ' ');
                        if (i < remainingSpaces) lineStr += ' ';
                    }
                } else {
                    lineStr += line[0];
                    lineStr += string(maxWidth - lineStr.length(), ' ');
                }
                res.emplace_back(lineStr);
                line.clear();
                lineStr.clear();
                count = 0;
            }
            line.emplace_back(words[i]);
            count += words[i].length();
            if (i == words.size() - 1) {
                for (int i = 0; i < line.size(); ++i) {
                    lineStr += line[i];
                    if (i != line.size() - 1)
                        lineStr += ' ';
                    else
                        lineStr += string(maxWidth - lineStr.length(), ' ');
                }
                res.emplace_back(lineStr);
            }
        }

        return res;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<string>> inputWords{
        {"This", "is", "an", "example", "of", "text", "justification."},
        {"What", "must", "be", "acknowledgment", "shall", "be"},
        {"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to", "a",
            "computer.","Art","is","everything","else","we","do"}
    };

    vector<int> inputWidths{16, 16, 20};

    if (inputWidths.size() != inputWords.size()) {
        std::cout << "Incorrect test inputs\n";
        return -1;
    }

    for (int i = 0; i < inputWords.size(); ++i) {
        auto res = s.fullJustify(inputWords[i], inputWidths[i]);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &line : res) {
            std::cout << "    [";
            std::cout << line;
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    }
}