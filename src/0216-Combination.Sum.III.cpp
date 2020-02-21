/**
 * Find all possible combinations of k numbers that add up to a number n, given that only numbers
 * from 1 to 9 can be used and each combination should be a unique set of numbers.
 *
 * Note:
 * All numbers will be positive integers.
 * The solution set must not contain duplicate combinations.
 *
 * Example 1:
 * Input: k = 3, n = 7
 * Output: [[1,2,4]]
 *
 * Example 2:
 * Input: k = 3, n = 9
 * Output: [[1,2,6], [1,3,5], [2,3,4]]
 */

#include "MyMisc.h"

#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<std::vector<int>> combinationSum3(int k, int n) {
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        backtrace(result, path, k, n, 1);
        return result;
    }

private:
    void backtrace(std::vector<std::vector<int>> &result, std::vector<int> &path, int k, int n,
            int start) {
        auto end = 10 - k;
        if (end < start) return;
        if (k == 0) {
            if (n == 0) {
                result.emplace_back(path);
            }
            return;
        }
        for (auto i = start; i <= end && i <= n; ++i) {
            path.emplace_back(i);
            backtrace(result, path, k - 1, n - i, i + 1);
            path.pop_back();
        }
    }
};

struct Input {
    int k;
    int n;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{3, 7}, {3, 9}};

    auto print_v = [](const std::vector<int> &vs) {
        std::cout << "[";
        for (auto &v : vs) std::cout << v << ", ";
        std::cout << "]";
    };

    auto print_vv = [&print_v](const std::vector<std::vector<int>> &vvs) {
        std::cout << "[";
        for (auto &vs : vvs) {
            print_v(vs);
            std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &input : inputs) {
        TestCount();
        print_vv(sln.combinationSum3(input.k, input.n));
    }
}