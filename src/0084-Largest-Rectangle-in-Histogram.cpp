/**
 * Given n non-negative integers representing the histogram's bar height where the width of each bar
 * is 1, find the area of largest rectangle in the histogram.
 *
 * [histogram](https://assets.leetcode.com/uploads/2018/10/12/histogram.png)
 * Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
 *
 * [largest_rectangle](https://assets.leetcode.com/uploads/2018/10/12/histogram_area.png)
 * The largest rectangle is shown in the shaded area, which has area = 10 unit.
 *
 * Example:
 * Input: [2,1,5,6,2,3]
 * Output: 10
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;
using std::min;

class Solution {
public:
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

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> heightsVec{
        {2, 1, 5, 6, 2, 3},
        {1, 2, 3, 4, 5, 6},
        {2, 1, 2},
        {1, 2, 2}
    };

    for (auto &heights : heightsVec) {
        auto rec = s.largestRectangleArea(heights);
        std::cout << "Case " << testId++ << ": " << rec << std::endl;
    }
}