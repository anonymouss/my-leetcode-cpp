/**
 * Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai).
 * n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two
 * lines, which together with x-axis forms a container, such that the container contains the most water.
 *
 * Note: You may not slant the container and n is at least 2.
 *
 *    /|
 *     |
 *  8 -|          |*|                           |*|
 *     |          |\|                           | |
 *  7 -|          |\|---------------------------| |---------|*|
 *     |          |\|  .  .  .  .  .  .  .  .  .| |  .  .  .|\|
 *  6 -|          |\|  .|*|  .  .  .  .  .  .  .| |  .  .  .|\|
 *     |          |\|  .| |  .  .  .  .  .  .  .| |  .  .  .|\|
 *  5 -|          |\|  .| |  .  .  .|*|  .  .  .| |  .  .  .|\|
 *     |          |\|  .| |  .  .  .| |  .  .  .| |  .  .  .|\|
 *  4 -|          |\|  .| |  .  .  .| |  .|*|  .| |  .  .  .|\|
 *     |          |\|  .| |  .  .  .| |  .| |  .| |  .  .  .|\|
 *  3 -|          |\|  .| |  .  .  .| |  .| |  .| |  .|*|  .|\|
 *     |          |\|  .| |  .  .  .| |  .| |  .| |  .| |  .|\|
 *  2 -|          |\|  .| |  .|*|  .| |  .| |  .| |  .| |  .|\|
 *     |          |\|  .| |  .| |  .| |  .| |  .| |  .| |  .|\|
 *  1 -|    |*|   |\|  .| |  .| |  .| |  .| |  .| |  .| |  .|\|
 *     |____|_|___|\|__.|_|__.|_|__.|_|__.|_|__.|_|__.|_|__.|\|__________
 *    0      1     2     3     4     5     6     7     8     9     10
 *
 * The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of
 * water (blue section) the container can contain is 49.
 *
 * Example:
 * Input: [1,8,6,2,5,4,8,3,7]
 * Output: 49
 */

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERSION 1
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#if (COMPILE_VERSION == 0)
// brute force solution
class Solution {
public:
    int maxArea(vector<int>& height) {
        auto size = height.size();
        int maxArea = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                auto area = MIN(height[i], height[j]) * (j - i);
                maxArea = maxArea > area ? maxArea : area;
            }
        }
        return maxArea;
    }
};
#elif (COMPILE_VERSION == 1)
// two pointers
class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0, area = 0, l = 0, r = static_cast<int>(height.size()) - 1;
        while (l < r) {
            if (height[l] > height[r]) {
                area = height[r] * (r - l);
                --r;
            } else {
                area = height[l] * (r - l);
                ++l;
            }
            maxArea = maxArea > area ? maxArea : area;
        }
        return maxArea;
    }
};
#endif

int main() {
    Solution s;

    vector<int> heights1{1, 8, 6, 2, 5, 4, 8, 3, 7};

    std::cout << "Case 1: " << s.maxArea(heights1) << std::endl;
}