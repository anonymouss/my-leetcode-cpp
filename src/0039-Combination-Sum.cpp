/**
 * Given a set of candidate numbers (candidates) (without duplicates) and a
 * target number (target), find all unique combinations in candidates where the
 * candidate numbers sums to target.
 *
 * The same repeated number may be chosen from candidates unlimited number of
 * times.
 *
 * Note:
 * All numbers (including target) will be positive integers.
 * The solution set must not contain duplicate combinations.
 *
 * Example 1:
 * Input: candidates = [2,3,6,7], target = 7,
 * A solution set is:
 * [
 *   [7],
 *   [2,2,3]
 * ]
 *
 * Example 2:
 * Input: candidates = [2,3,5], target = 8,
 * A solution set is:
 * [
 *   [2,2,2,2],
 *   [2,3,3],
 *   [3,5]
 * ]
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        if (candidates.empty()) return res;
        vector<int> calculated;
        calculateFrom(candidates, calculated, 0, target, res);
        return res;
    }

    // backtracing
    void calculateFrom(vector<int> &candidates, vector<int> &calculated, int from,
            int target, vector<vector<int>> &res) {
        if (target == 0) {
            res.emplace_back(calculated);
            return;
        } else {
            for (int i = from; i < candidates.size(); ++i) {
                if (candidates[i] <= target) {
                    calculated.emplace_back(candidates[i]);
                    calculateFrom(candidates, calculated, i /* repeat */,
                            target - candidates[i], res);
                    calculated.pop_back(); // backtracing
                }
            }
        }
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<int> candidates1{2, 3, 6, 7}; int target1 = 7;
    vector<int> candidates2{2, 3, 5}; int target2 = 8;

    auto exeTest = [&](vector<int> &candidates, int target) {
        auto res = s.combinationSum(candidates, target);
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