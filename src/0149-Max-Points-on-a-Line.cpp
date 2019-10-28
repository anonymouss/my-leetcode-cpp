/**
 * Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
 * Example 1:
 * Input: [[1,1],[2,2],[3,3]]
 * Output: 3
 * Explanation:
 * ^
 * |
 * |        o
 * |     o
 * |  o  
 * +------------->
 * 0  1  2  3  4
 *
 * Example 2:
 * Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
 * Output: 4
 * Explanation:
 * ^
 * |
 * |  o
 * |     o        o
 * |        o
 * |  o        o
 * +------------------->
 * 0  1  2  3  4  5  6
 */

#include "../utils/MyMisc.h"

#include <vector>
#include <unordered_map>
#include <set>
#include <limits>
#include <numeric>

using std::vector;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        if (points.empty()) return 0;
        // max points count, sorted
        std::set<int> max_points;
        // slope, current points count
        std::unordered_map<long double, int> slope_map;
        for (const auto &this_point : points) {
            int max = 0, same = 0;
            slope_map.clear();
            for (const auto &that_point : points) {
                // skip same
                if (this_point == that_point) {
                    ++same;
                    continue;
                }
                auto x_dist = static_cast<long double>(this_point[0] - that_point[0]);
                auto y_dist = static_cast<long double>(this_point[1] - that_point[1]);
                auto slope =
                    (x_dist == 0.0)
                        ? std::numeric_limits<long double>::infinity()
                        : y_dist / x_dist;
                slope_map[slope]++;
                if (slope_map[slope] > max) max = slope_map[slope];
            }
            max_points.emplace(max + same);
        }
        return *max_points.rbegin();
    }
};

int main() {
    Solution s; 
    std::vector<std::vector<std::vector<int>>> inputs {
        {{1, 1}, {2, 2}, {3, 3}},
        {{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}},
        {},
        {{1, 1}, {1, 1}},
        {{0, 0}, {1, 1}, {1, -1}},
        {{1, 1}, {1, 1}, {2, 2}, {2, 2}},
        {{0,0}, {94911151,94911150}, {94911152,94911151}}
    };

    for (auto &input : inputs) {
        TestCount();
        std::cout << "max points: " << s.maxPoints(input) << std::endl;
    }
}