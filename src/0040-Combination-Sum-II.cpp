/**
 * Given a collection of candidate numbers (candidates) and a target number
 * (target), find all unique combinations in candidates where the candidate
 * numbers sums to target.
 * Each number in candidates may only be used once in the combination.
 *
 * Note:
 * - All numbers (including target) will be positive integers.
 * - The solution set must not contain duplicate combinations.
 *
 * Example 1:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8,
 * A solution set is:
 * [
 *   [1, 7],
 *   [1, 2, 5],
 *   [2, 6],
 *   [1, 1, 6]
 * ]
 *
 * Example 2:
 * Input: candidates = [2,5,2,1,2], target = 5,
 * A solution set is:
 * [
 *   [1,2,2],
 *   [5]
 * ]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;
using std::any_of;

#define COMPILE_VERSION 1

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        if (candidates.empty()) return res;
        sort(candidates.begin(), candidates.end());
        vector<int> calculated;
        calculateFrom(candidates, calculated, 0, target, res);
        return res;
    }

#if (COMPILE_VERSION == 0)
    void calculateFrom(vector<int> &candidates, vector<int> &calculated, int from,
            int target, vector<vector<int>> &res) {
        if (target == 0) {
            if (!any_of(res.begin(), res.end(), [&calculated](const vector<int> &v) {
                        if (v.size() != calculated.size()) return false;
                        for (auto i = 0; i < v.size(); ++i) {
                            if (v[i] != calculated[i]) return false;
                        }
                        return true;
                    }))
                res.emplace_back(calculated);
            return;
        } else {
            for (int i = from; i < candidates.size(); ++i) {
                if (candidates[i] <= target) {
                    calculated.emplace_back(candidates[i]);
                    calculateFrom(candidates, calculated, i + 1 /* use once */,
                            target - candidates[i], res);
                    calculated.pop_back(); // backtracing
                }
            }
        }
    }
#elif (COMPILE_VERSION == 1)
    void calculateFrom(vector<int> &candidates, vector<int> &calculated, int from,
            int target, vector<vector<int>> &res) {
        if (target == 0) {
            res.emplace_back(calculated);
            return;
        } else {
            for (int i = from; i < candidates.size(); ++i) {
                if (candidates[i] <= target) {
                    if ( i > from && candidates[i] == candidates[i - 1]) continue;
                    calculated.emplace_back(candidates[i]);
                    calculateFrom(candidates, calculated, i + 1 /* use once */,
                            target - candidates[i], res);
                    calculated.pop_back(); // backtracing
                }
            }
        }
    }
#endif
};

int main() {
    Solution s;
    int testId = 1;

    vector<int> candidates1{10, 1, 2, 7, 6, 1, 5}; int target1 = 8;
    vector<int> candidates2{2, 5, 2, 1, 2}; int target2 = 5;

    auto exeTest = [&](vector<int> &candidates, int target) {
        auto res = s.combinationSum2(candidates, target);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &v : res) {
            std::cout << "    [";
            for (const auto &e : v)
                std::cout << e << ", ";
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    };

    exeTest(candidates1, target1);
    exeTest(candidates2, target2);
}