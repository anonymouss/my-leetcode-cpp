/**
 * Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral
 * order.
 *
 * Example 1:
 * Input:
 * [
 *  [ 1, 2, 3 ],
 *  [ 4, 5, 6 ],
 *  [ 7, 8, 9 ]
 * ]
 * Output: [1,2,3,6,9,8,7,4,5]
 *
 * Example 2:
 * Input:
 * [
 *   [1, 2, 3, 4],
 *   [5, 6, 7, 8],
 *   [9,10,11,12]
 * ]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.empty() || matrix[0].empty()) return res;
        int m = matrix.size(), n = matrix[0].size();
        int sm = 0, sn = 0;
        int size = m * n;
        while (res.size() < size) {
            for (int u = sn; u < n; ++u)
                res.emplace_back(matrix[sm][u]);
            for (int r = sm + 1; r < m; ++r)
                res.emplace_back(matrix[r][n - 1]);
            for (int b = n - 2; b >= sn && sm < m - 1; --b)
                res.emplace_back(matrix[m - 1][b]);
            for (int l = m - 2; l > sm && sn < n - 1; --l)
                res.emplace_back(matrix[l][sn]);
            ++sm; ++sn; --m; --n;
        }
        return res;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<vector<int>>> matrixes{
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        },
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        },
        {
            {6, 9, 7}
        }
    };

    for (auto &matrix : matrixes) {
        auto res = s.spiralOrder(matrix);
        std::cout << "Case " << testId++ << ": [";
        for (const auto &e : res) std::cout << e << ", ";
        std::cout << "]" << std::endl;
    }
}