// 在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成
// 一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
// 
// 示例:
// 现有矩阵 matrix 如下：
// [
//   [1,   4,  7, 11, 15],
//   [2,   5,  8, 12, 19],
//   [3,   6,  9, 16, 22],
//   [10, 13, 14, 17, 24],
//   [18, 21, 23, 26, 30]
// ]
// 给定 target = 5，返回 true。
// 给定 target = 20，返回 false。
// 
// 限制：
// 0 <= n <= 1000
// 0 <= m <= 1000
// 
// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include <vector>

#if 0
class Solution {
public:
    // binary search
    bool findNumberIn2DArray(std::vector<std::vector<int>> &matrix, int target) {
        auto rows = matrix.size();
        if (rows == 0) return false;
        auto cols = matrix[0].size();
        if (cols == 0) return false;
        return findNumberIn2DArray_l(matrix, target, 0, cols - 1, 0, rows - 1);
    }

private:
    bool findNumberIn2DArray_l(std::vector<std::vector<int>> &mat, int tar,
            int left, int right, int up, int bottom) {
        if (left > right || up > bottom) {
            return false;
        }

        auto mid_v = (up + bottom) / 2;
        auto mid_h = (left + right) / 2;
        auto val = mat[mid_v][mid_h];
        if (val == tar) {
            return true;
        }

        if (left == right && up == bottom) {
            return false;
        }

        if (val < tar) {
            return findNumberIn2DArray_l(mat, tar, mid_h + 1, right, up, bottom)
                    || findNumberIn2DArray_l(mat, tar, left, mid_h, mid_v + 1, bottom);
        } else {
            return findNumberIn2DArray_l(mat, tar, left, right, up, mid_v - 1)
                    || findNumberIn2DArray_l(mat, tar, left, mid_h - 1, up, bottom);
        }
    }
};
#endif

class Solution {
public:
    bool findNumberIn2DArray(std::vector<std::vector<int>> &matrix, int target) {
        int i = matrix.size() - 1, j = 0;
        while(i >= 0 && j < matrix[0].size())
        {
            if(matrix[i][j] > target) i--;
            else if(matrix[i][j] < target) j++;
            else return true;
        }
        return false;
    }
};


int main() {
    Solution s;

    std::vector<std::vector<int>> mat{
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };

    std::vector<int> targets{5, 20};

    for (const auto &t : targets) {
        std::cout << "[target]: " << t << " [result]: " << std::boolalpha
                << s. findNumberIn2DArray(mat, t) << std::endl;
    }
}