/**
 * You are given an n x n 2D matrix representing an image.
 * Rotate the image by 90 degrees (clockwise).
 *
 * Note:
 * You have to rotate the image in-place, which means you have to modify the
 * input 2D matrix directly. DO NOT allocate another 2D matrix and do the
 * rotation.
 *
 * Example 1:
 * Given input matrix = 
 * [
 *   [1,2,3],
 *   [4,5,6],
 *   [7,8,9]
 * ],
 * rotate the input matrix in-place such that it becomes:
 * [
 *   [7,4,1],
 *   [8,5,2],
 *   [9,6,3]
 * ]
 *
 * Example 2:
 * Given input matrix =
 * [
 *   [ 5, 1, 9,11],
 *   [ 2, 4, 8,10],
 *   [13, 3, 6, 7],
 *   [15,14,12,16]
 * ], 
 * rotate the input matrix in-place such that it becomes:
 * [
 *   [15,13, 2, 5],
 *   [14, 3, 4, 1],
 *   [12, 6, 8, 9],
 *   [16, 7,10,11]
 * ]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::reverse;
using std::swap;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int layer = 0; layer <= n / 2; ++layer) {
            for (int pos = layer; pos < n - layer -1; ++pos) {
                int val = matrix[layer][pos];
                matrix[layer][pos] = matrix[n - pos - 1][layer];
                matrix[n - pos - 1][layer] = matrix[n - layer - 1][n - pos - 1];
                matrix[n - layer - 1][n - pos - 1] = matrix[pos][n - layer - 1];
                matrix[pos][n - layer -1] = val;
            }
        }
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    void rotate(vector<vector<int>> &matrix) {
        int n = matrix.size();
        reverse(matrix.begin(), matrix.end());

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<vector<vector<int>>> maxtrixes{
        {
            {1, 2, 3},  // 7, 4, 1
            {4, 5, 6},  // 8, 5, 2
            {7, 8, 9},  // 9, 6, 3
        },
        {
            {5, 1, 9, 11},
            {2, 4, 8, 10},
            {13, 3, 6, 7},
            {15, 14, 12, 16}
        }
    };

    for (auto &matrix : maxtrixes) {
        s.rotate(matrix);
        std::cout << "Case " << testId++ << ":\n  [\n";
        for (const auto &v : matrix) {
            std::cout << "    [";
            for (const auto &e : v)
                std::cout << e << ", ";
            std::cout << "]" << std::endl;
        }
        std::cout << "  ]" << std::endl;
    }
}