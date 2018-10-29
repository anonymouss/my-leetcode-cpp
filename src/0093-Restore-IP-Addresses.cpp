/**
 * Given a string containing only digits, restore it by returning all possible valid IP address
 * combinations.
 *
 * Example:
 * Input: "25525511135"
 * Output: ["255.255.11.135", "255.255.111.35"]
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        if (s.length() < 4 || s.length() > 12) return res;
        string t{""};
        dfs(s, t, res, 0);
        return res;
    }

    void dfs(string &s, string &t, vector<string> &res, int cnt) {
        if (cnt == 3 && isValid(s)) {
            res.emplace_back(t+s);
            return;
        }
        for (int i = 1; i < 4 && i < s.length(); ++i) {
            auto subs = s.substr(0, i);
            if (isValid(subs)) {
                auto ss = s.substr(i), ts = t + subs + ".";
                dfs(ss, ts, res, cnt+1);
            }
        }
    }

    int strToInt(string s) {
        int res = 0;
        for (const auto &c : s)
            res = 10 * res + (c - '0');
        return res;
    }

    bool isValid(string s) {
        if (s.empty() || s.length() > 4) return false;
        if (s[0] == '0') return s == "0";
        auto i = strToInt(s);
        return i > 0 && i <= 255;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<string> strs{
        "25525511135"
    };

    for (auto &str : strs) {
        auto ips = s.restoreIpAddresses(str);
        std::cout << "Case " << testId++ << ": [";
        for (const auto &ip : ips) std::cout << ip << ", ";
        std::cout << "]" << std::endl;
    }
}