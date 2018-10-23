/**
 * Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral
 * order.
 *
 * Example:
 * Input: 3
 * Output:
 * [
 *  [ 1, 2, 3 ],
 *  [ 8, 9, 4 ],
 *  [ 7, 6, 5 ]
 * ]
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int s = 0, e = 1, end = n * n;
        while (e <= end) {
            for (int i = s; i < n - s; ++i)
                res[s][i] = e++;
            for (int i = s + 1; i < n - s; ++i)
                res[i][n - s - 1] = e++;
            for (int i = n - s - 2; i >= s; --i)
                res[n - s - 1][i] = e++;
            for (int i = n - s - 2; i > s; --i)
                res[i][s] = e++;
            ++s;
        }
        return res;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<int> ns{3, 4, 5};

    for (auto &n : ns) {
        auto res = s.generateMatrix(n);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &line : res) {
            std::cout << "    [";
            for (const auto &e : line)
                std::cout << e << ", ";
            std::cout << "],\n";
        }
        std::cout << "  ]" << std::endl;
    }
}