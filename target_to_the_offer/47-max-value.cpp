/* 在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿
格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你
最多能拿到多少价值的礼物？

示例 1:
输入: 
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 12
解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物

提示：
0 < grid.length <= 200
0 < grid[0].length <= 200

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <vector>
#include <iostream>

class Solution {
public:
    int maxValue(std::vector<std::vector<int>> &grid) {
        auto rows = grid.size();
        if (rows == 0) return 0;
        auto cols = grid[0].size();
        int *dp = new int[(rows + 1) * (cols + 1)];

        for (auto r = 0; r <= rows; ++r) {
            for (auto c = 0; c <= cols; ++c) {
                if (r == 0 || c == 0) {
                    dp[r * (cols + 1) + c] = 0;
                } else {
                    dp[r * (cols + 1) + c] = grid[r - 1][c - 1]
                            + std::max(dp[(r - 1) * (cols + 1) + c], dp[r * (cols + 1) + c - 1]);
                }

            }
        }

        auto ret = dp[rows * (cols + 1) + cols];
        delete [] dp;
        return ret;
    }
};

int main() {
    Solution s;

    using Board = std::vector<std::vector<int>>;
    std::vector<Board> is{
        {
            {1, 3, 1},
            {1, 5, 1},
            {4, 2, 1}
        }
    };

    for (auto &i : is) {
        std::cout << s.maxValue(i) << std::endl;
    }
}
