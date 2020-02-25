/**
 * Find the total area covered by two rectilinear rectangles in a 2D plane.
 * Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
 *
 * Example:
 * Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
 * Output: 45
 *
 * Note:
 * Assume that the total area is never beyond the maximum possible value of int.
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        auto overlap = 0;
        bool noOverlap = C <= E || A >= G || B >= H || D <= F;
        if (!noOverlap) {
            auto left = std::max(A, E), right = std::min(C, G), top = std::min(D, H),
                bottom = std::max(B, F);
            overlap = (left - right) * (bottom - top);
        }
        auto area1 = (A - C) * (B - D);
        auto area2 = (E - G) * (F - H);
        return area1 - overlap + area2;
    }
};

struct Corners {
    int A;
    int B;
    int C;
    int D;
    int E;
    int F;
    int G;
    int H;
};

int main() {
    Solution sln;

    std::vector<Corners> corners{
        {-3, 0, 3, 4, 0, -1, 9, 2},
        {-2, -2, 2, 2, 3, 3, 4, 4},
        {0, 0, 50000, 40000, 0, 0, 50000, 40000}
    };

    for (auto &c : corners) {
        TestCount();
        std::cout << sln.computeArea(c.A, c.B, c.C, c.D, c.E, c.F, c.G, c.H) << std::endl;
    }
}