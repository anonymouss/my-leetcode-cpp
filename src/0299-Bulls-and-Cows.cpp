/**
 * You are playing the following Bulls and Cows game with your friend: You write down a number and
 * ask your friend to guess what the number is. Each time your friend makes a guess, you provide a
 * hint that indicates how many digits in said guess match your secret number exactly in both digit
 * and position (called "bulls") and how many digits match the secret number but locate in the wrong
 * position (called "cows"). Your friend will use successive guesses and hints to eventually derive
 * the secret number.
 *
 * Write a function to return a hint according to the secret number and friend's guess, use A to
 * indicate the bulls and B to indicate the cows.  Please note that both secret number and friend's
 * guess may contain duplicate digits.
 *
 * Example 1:
 * Input: secret = "1807", guess = "7810"
 * Output: "1A3B"
 * Explanation: 1 bull and 3 cows. The bull is 8, the cows are 0, 1 and 7.
 *
 * Example 2:
 * Input: secret = "1123", guess = "0111"
 * Output: "1A1B"
 * Explanation: The 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow.
 *
 * Note: You may assume that the secret number and your friend's guess only contain digits, and
 * their lengths are always equal.
 */

#include "MyMisc.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Solution {
public:
    std::string getHint(std::string secret, std::string guess) {
        int acount = 0, bcount = 0;
        int smap[10] = {0}, gmap[10] = {0};
        for (std::size_t i = 0; i < secret.length(); ++i) {
            if (secret[i] == guess[i]) {
                ++acount;
            } else {
                smap[secret[i] - '0']++;
                gmap[guess[i] - '0']++;
            }
        }
        for (auto i = 0; i <= 9; ++i) {
            auto s = smap[i];
            auto g = gmap[i];
            if (s > 0 && g > 0) { bcount += (s > g) ? g : s; }
        }
        return std::to_string(acount) + "A" + std::to_string(bcount) + "B";
    }
};

struct Input {
    std::string secret;
    std::string guess;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{
        {"1807", "7810"}, {"1123", "0111"}, {"1122", "2211"}, {"0194", "9038"}};

    for (auto &input : inputs) {
        TestCount();
        std::cout << sln.getHint(input.secret, input.guess) << std::endl;
    }
}