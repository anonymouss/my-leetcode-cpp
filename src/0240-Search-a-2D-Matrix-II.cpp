/**
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the
 * following properties:
 *
 * Integers in each row are sorted in ascending from left to right.
 * Integers in each column are sorted in ascending from top to bottom.
 *
 * Example:
 * Consider the following matrix:
 * [
 *   [1,   4,  7, 11, 15],
 *   [2,   5,  8, 12, 19],
 *   [3,   6,  9, 16, 22],
 *   [10, 13, 14, 17, 24],
 *   [18, 21, 23, 26, 30]
 * ]
 * Given target = 5, return true.
 * Given target = 20, return false.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target) {
        int rows = matrix.size();
        if (rows == 0) return false;
        int cols = matrix[0].size();

        int row = rows - 1;
        int col = 0;
        while (row >= 0 && col < cols) {
            if (matrix[row][col] > target) {
                --row;
            } else if (matrix[row][col] < target) {
                ++col;
            } else {
                return true;
            }
        }
        return false;
    }
};

struct Input {
    std::vector<std::vector<int>> matrix;
    int target;

    Input(std::vector<std::vector<int>> _matrix, int _target)
        : matrix(_matrix), target(_target) {}
};

int main() {
    Solution sln;

    std::vector<std::vector<int>> mat1{
        {1,   4,  7, 11, 15},
        {2,   5,  8, 12, 19},
        {3,   6,  9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };

    std::vector<Input> inputs{
        {mat1, 5},
        {mat1, 20}
    };

    for (auto &input : inputs) {
        TestCount(IOFormat::BOOL);
        std::cout << sln.searchMatrix(input.matrix, input.target) << std::endl;
    }
}