/**
 * The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a
 * dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was
 * initially positioned in the top-left room and must fight his way through the dungeon to rescue
 * the princess.
 *
 * The knight has an initial health point represented by a positive integer. If at any point his
 * health point drops to 0 or below, he dies immediately.
 *
 * Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon
 * entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the
 * knight's health (positive integers).
 *
 * In order to reach the princess as quickly as possible, the knight decides to move only rightward
 * or downward in each step.
 *
 * Write a function to determine the knight's minimum initial health so that he is able to rescue
 * the princess.
 *
 * For example, given the dungeon below, the initial health of the knight must be at least 7 if he
 * follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
 *
 * -2 (K)	-3	    3
 * -5	    -10	    1
 * 10	    30	    -5 (P)
 *
 * Note:
 * The knight's health has no upper bound.
 * Any room can contain threats or power-ups, even the first room the knight enters and the
 * bottom-right room where the princess is imprisoned.
 */

#include "MyMisc.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

class Solution {
public:
    int calculateMinimumHP(std::vector<std::vector<int>> &dungeon) {
        auto rows = dungeon.size(), cols = dungeon[0].size();
        std::vector<int> dp(cols + 1, INT32_MAX);
        dp[cols - 1] = dungeon[rows - 1][cols - 1] > 0 ? 1 : -dungeon[rows - 1][cols - 1] + 1;
        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 0; j--) {
                if (i == rows - 1 && j == cols - 1) { continue; }
                dp[j] = std::min(dp[j], dp[j + 1]) - dungeon[i][j];
                if (dp[j] <= 0) { dp[j] = 1; }
            }
        }
        return dp[0];
    }
};

int main() {
    Solution sln;
    std::vector<std::vector<std::vector<int>>> dungeons{{{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}}};

    for (auto &dungeon : dungeons) {
        TestCount();
        std::cout << "min initial health points: " << sln.calculateMinimumHP(dungeon) << std::endl;
    }
}