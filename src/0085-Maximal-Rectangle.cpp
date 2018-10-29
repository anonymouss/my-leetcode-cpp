/**
 * Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's
 * and return its area.
 *
 * Example:
 * Input:
 * [
 *   ["1","0","1","0","0"],
 *   ["1","0","1","1","1"],
 *   ["1","1","1","1","1"],
 *   ["1","0","0","1","0"]
 * ]
 * Output: 6
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;
using std::min;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        int maxRec = 0;
        vector<int> heights(matrix[0].size());
        for (const auto& vec : matrix) {
            for (int i = 0; i < vec.size(); ++i) {
                // including upper layer's val
                heights[i] = vec[i] == '0' ? 0 : (heights[i] + 1);
            }
            maxRec = max(maxRec, largestRectangleArea(heights));
        }
        return maxRec;
    }

    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0;
        for (int i = 0; i < heights.size(); ++i) {
            if (i < heights.size() - 1 && heights[i] <= heights[i+1]) continue;
            int minHeight = heights[i];
            for (int j = i; j >= 0; --j) {
                minHeight = min(minHeight, heights[j]);
                int area = (i - j + 1) * minHeight;
                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> height(n, 0), left(n, 0), right(n, n);
        int maxRec = 0;
        for (int r = 0; r < m; ++r) {
            int curLeft = 0, curRight = n;
            for (int c = 0; c < n; ++c) {
                height[c] = matrix[r][c] == '0' ? 0 : (height[c] + 1);

                if (matrix[r][c] == '0') {
                    left[c] = 0;
                    curLeft = c + 1;
                } else {
                    left[c] = max(curLeft, left[c]);
                }
            }
            for (int c = n - 1; c >= 0; --c) {
                if (matrix[r][c] == '0') {
                    right[c] = n;
                    curRight = c;
                } else {
                    right[c] = min(curRight, right[c]);
                }

                maxRec = max(maxRec, (right[c] - left[c]) * height[c]);
            }
        }
        return maxRec;
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<vector<vector<char>>> matrixes{
        {
            {'1', '0', '1', '0', '0'},
            {'1', '0', '1', '1', '1'},
            {'1', '1', '1', '1', '1'},
            {'1', '0', '0', '1', '0'}
        },
        {
            {'0', '0', '1', '0', '0'},
            {'0', '0', '1', '1', '1'},
            {'0', '0', '1', '1', '0'},
            {'1', '0', '0', '1', '0'}
        }
    };

    for (auto &matrix : matrixes) {
        auto rec = s.maximalRectangle(matrix);
        std::cout << "Case " << testId++ << ": " << rec << std::endl;
    }
}