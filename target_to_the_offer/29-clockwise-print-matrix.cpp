/* 输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

示例 1：
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]

示例 2：
输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
 
限制：
0 <= matrix.length <= 100
0 <= matrix[i].length <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>> &matrix) {
        auto rows = matrix.size();
        if (rows == 0) return {};
        auto cols = matrix[0].size();
        std::vector<int> res;
        int r_top = 0, r_bottom = rows - 1;
        int c_left = 0, c_right = cols - 1;
        bool skip_h = false, skip_v = false;
        while (r_top <= r_bottom && c_left <= c_right) {
            if (!skip_h) {
                for (auto i = c_left; i <= c_right; ++i) {
                    res.emplace_back(matrix[r_top][i]);
                }
                if (r_top >= r_bottom) skip_h = true;
            }
            if (!skip_v) {
                for (auto i = r_top + 1; i <= r_bottom; ++i) {
                    res.emplace_back(matrix[i][c_right]);
                }
                if (c_left >= c_right) skip_v = true;
            }
            if (!skip_h) {
                for (auto i = c_right - 1; i >= c_left; --i) {
                    res.emplace_back(matrix[r_bottom][i]);
                }
                if (r_top >= r_bottom) skip_h = true;
            }
            if (!skip_v) {
                for (auto i = r_bottom - 1; i > r_top; --i) {
                    res.emplace_back(matrix[i][c_left]);
                }
                if (c_left >= c_right) skip_v = true;
            }

            r_top++; r_bottom--;
            c_left++; c_right--;
        }
        return res;
    }
};

int main() {
    Solution s;
    using Mat = std::vector<std::vector<int>>;

    std::vector<Mat> inputs{
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
        {},
        {
            {2, 5, 8},
            {4, 0, -1}
        }
    };

    auto print_v = [](const std::vector<int> &v) {
        for (const auto &i : v) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    };

    for (auto &mat : inputs) {
        print_v(s.spiralOrder(mat));
    }
}