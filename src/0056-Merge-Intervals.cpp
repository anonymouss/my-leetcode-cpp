/**
 * Given a collection of intervals, merge all overlapping intervals.
 *
 * Example 1:
 * Input: [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
 *
 * Example 2:
 * Input: [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considerred overlapping.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](Interval a, Interval b) {
                                                        return a.start < b.start;
                                                    });
        vector<Interval> res;
        for (const auto &iv : intervals) {
            if (res.empty() || res.back().end < iv.start) {
                res.emplace_back(iv);
            } else {
                res.back().end = res.back().end > iv.end ?
                                    res.back().end : iv.end;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    int testId = 1;

    // test cases
    vector<vector<vector<int>>> ints{
        {
            {1, 3}, {2, 6}, {8, 10}, {15, 18}
        },
        {
            {1, 4}, {4, 5}
        },
        {
            {1, 4}, {0, 4}
        },
        {
            {1, 4}, {0, 0}
        },
        {
            // empty
        }
    };

    for (auto &vec : ints) {
        vector<Interval> intervals;
        auto genInputs = [&](vector<vector<int>> &vec) {
            intervals.clear();
            for (auto &v : vec) {
                intervals.emplace_back(Interval(v[0], v[1]));
            }
        };

        genInputs(vec);
        auto res = s.merge(intervals);
        std::cout << "Case " << testId++ << ": [";
        for (const auto &i : res) {
            std::cout << "[" << i.start << ", " << i.end << "], ";
        }
        std::cout << "]" << std::endl;
    }
}