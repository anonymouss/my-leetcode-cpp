/**
 * Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.
 *
 * Example 1:
 * Input:
 * [
 *   [1,1,1],
 *   [1,0,1],
 *   [1,1,1]
 * ]
 * Output:
 * [
 *   [1,0,1],
 *   [0,0,0],
 *   [1,0,1]
 * ]
 *
 * Example 2:
 * Input:
 * [
 *   [0,1,2,0],
 *   [3,4,5,2],
 *   [1,3,1,5]
 * ]
 * Output:
 * [
 *   [0,0,0,0],
 *   [0,4,5,0],
 *   [0,3,1,0]
 * ]
 *
 * Follow up:
 * - A straight forward solution using O(mn) space is probably a bad idea.
 * - A simple improvement uses O(m + n) space, but still not the best solution.
 * - Could you devise a constant space solution?
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;
        int m = matrix.size(), n = matrix[0].size();
        bool isRow = false, isCol = false;
        // check if row 0 contains 0 / o(m)
        for (int col = 1; col < n; ++col) {
            if (matrix[0][col] == 0) {
                isRow = true;
                break;
            }
        }
        // check if col 0 contains 0 / o(n)
        for (int row = 1; row < m; ++row) {
            if (matrix[row][0] == 0) {
                isCol = true;
                break;
            }
        }
        // check matrix elements and mark corresponding row 0 and col 0 / o((m-1)*(n-1))
        for (int row = 1; row < m; ++row) {
            for (int col = 1; col < n; ++col) {
                if (matrix[row][col] == 0) {
                    matrix[0][col] = 0;
                    matrix[row][0] = 0;
                }
            }
        }
        // fill matrix elements according to row 0 and col 0 / o((m-1)*(n-1))
        for (int row = 1; row < m; ++row) {
            for (int col = 1; col < n; ++col) {
                if (matrix[0][col] == 0 || matrix[row][0] == 0)
                    matrix[row][col] = 0;
            }
        }
        // fill row 0 and col 0 / o(m+n)
        if (matrix[0][0] == 0) {
            for (int col = 1; col < n; ++col) matrix[0][col] = 0;
            for (int row = 1; row < m; ++row) matrix[row][0] = 0;
        } else {
            if (isRow) {
                for (int col = 0; col < n; ++col) matrix[0][col] = 0;
            }
            if (isCol) {
                for (int row = 0; row < m; ++row) matrix[row][0] = 0;
            }
        }
        // total time complexity approximates to o(m*n), space o(1)
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<vector<int>>> matrixes{
        {
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1}
        },
        {
            {0, 1, 2, 0},
            {3, 4, 5, 2},
            {1, 3, 1, 5}
        },
        {
            {8, 3, 6, 9, 7, 8, 0, 6},
            {0, 3, 7, 0, 0, 4, 3, 8},
            {5, 3, 6, 7, 1, 6, 2, 6},
            {8, 7, 2, 5, 0, 6, 4, 0},
            {0,2 , 9, 9, 3, 9, 7, 3}
        }
    };

    for (auto &matrix : matrixes) {
        s.setZeroes(matrix);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &vec : matrix) {
            std::cout << "    [";
            for (const auto &e : vec)
                std::cout << e << ", ";
            std::cout << "]\n";
        }
        std::cout << "  ]" << std::endl;
    }
}