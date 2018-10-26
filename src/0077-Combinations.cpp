/**
 * Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
 *
 * Example:
 * Input: n = 4, k = 2
 * Output:
 * [
 *   [2,4],
 *   [3,4],
 *   [2,3],
 *   [1,2],
 *   [1,3],
 *   [1,4],
 * ]
 */

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERSION 1

// https://www.cnblogs.com/grandyang/p/4332522.html
#if (COMPILE_VERSION == 0)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> comb(k, 0);

        int i = 0;
        while (i >= 0) {
            ++comb[i];
            if (comb[i] > n) --i;
            else if (i == k - 1) res.emplace_back(comb);
            else {
                ++i;
                comb[i] = comb[i-1];
            }
        }
        return res;
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> comb;

        dfs(n, k, 1, comb, res);

        return res;
    }

    void dfs(int n, int k, int pos, vector<int> &comb, vector<vector<int>> &res) {
        if (comb.size() == k) {
            res.emplace_back(comb);
            return;
        }
        for (auto i = pos; i <= n; ++i) {
            comb.emplace_back(i);
            dfs(n, k, i + 1, comb, res);
            comb.pop_back();
        }
    }
};
#elif (COMPILE_VERSION == 2)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        if (k > n || k < 0) return {};
        if (k == 0) return {{}};

        auto res = combine(n-1, k-1);
        for (auto &comb : res) comb.emplace_back(n);
        for (const auto &comb : combine(n-1, k)) res.emplace_back(comb);
        return res;
    }
};
#endif

int main() {
    Solution s;
    int testId  =1;

    vector<vector<int>> nks{
        // n, k
        {4, 2}
    };

    for (const auto &nk : nks) {
        auto res = s.combine(nk[0], nk[1]);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &vec : res) {
            std::cout << "    [";
            for (const auto &e : vec)
                std::cout << e << ", ";
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    }
}