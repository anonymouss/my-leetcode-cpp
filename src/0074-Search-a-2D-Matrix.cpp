/**
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the
 * following properties:
 * - Integers in each row are sorted from left to right.
 * - The first integer of each row is greater than the last integer of the previous row.
 *
 * Example 1:
 * Input:
 * matrix = [
 *   [1,   3,  5,  7],
 *   [10, 11, 16, 20],
 *   [23, 30, 34, 50]
 * ]
 * target = 3
 * Output: true
 *
 * Example 2:
 * Input:
 * matrix = [
 *   [1,   3,  5,  7],
 *   [10, 11, 16, 20],
 *   [23, 30, 34, 50]
 * ]
 * target = 13
 * Output: false
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    // do bin search twice.
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int rows = matrix.size(), cols = matrix[0].size();
        if (target < matrix[0][0] || target > matrix[rows-1][cols-1]) return 0;
        int up = 0, down = rows - 1;
        // 1. find the candidate row that meets row[0] < target < next_row[0], which means target
        // may be in this row (bin search in rows)
        while (up < down) {
            int mid = (up + down) / 2;
            if (matrix[mid][0] > target) {
                down = mid;
            } else if (matrix[mid][0] < target) {
                if (matrix[mid][cols-1] >= target) {
                    up = mid;
                    break;
                }
                up = mid + 1;
            } else return true; // lucky find!
        }

        // 2. search in the candidate row (bin search in candidate row (cols))
        auto &candRow = matrix[up];
        int left = 0, right = cols - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (candRow[mid] > target)
                right = mid - 1;
            else if (candRow[mid] < target)
                left = mid + 1;
            else return true;
        }
        return false;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<vector<int>>> matrixes{
        {
            {1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 50}
        },
        {
            {1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 50}
        },
        {
            {1}
        },
        {
            {1},
            {3}
        }
    };

    vector<int> targets{3, 13, 1, 3};

    if (matrixes.size() != targets.size()) {
        std::cout << "incorrect test inputs\n";
        return -1;
    }

    for (int i = 0; i < matrixes.size(); ++i) {
        auto res = s.searchMatrix(matrixes[i], targets[i]);
        std::cout << std::boolalpha;
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}