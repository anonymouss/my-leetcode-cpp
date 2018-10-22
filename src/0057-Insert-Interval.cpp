/**
 * Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if
 * necessary).
 *
 * You may assume that the intervals were initially sorted according to their start times.
 *
 * Example 1:
 * Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * Output: [[1,5],[6,9]]
 *
 * Example 2:
 * Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * Output: [[1,2],[3,10],[12,16]]
 * Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
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
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        intervals.emplace_back(newInterval);
        return merge(intervals);
    }

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

    vector<vector<vector<int>>> ints{
        {
            {1, 3}, {6, 9}
        },
        {
            {1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}
        },
        {
            // empty
        },
        {
            {1, 5}
        },
        {
            {1, 5}
        }
    };

    vector<vector<int>> newInts{
        {2, 5},
        {4, 8},
        {5, 7},
        {6, 8},
        {0, 0}
    };

    if (ints.size() != newInts.size()) {
        std::cout << "Incorrect test inputs" << std::endl;
        return -1;
    }

    for (int i = 0; i < ints.size(); ++i) {
        vector<Interval> intervals;
        auto genInputs = [&](vector<vector<int>> &vec) {
            intervals.clear();
            for (auto &v : vec) {
                intervals.emplace_back(Interval(v[0], v[1]));
            }
        };

        genInputs(ints[i]);
        Interval newInterval(newInts[i][0], newInts[i][1]);
        auto res = s.insert(intervals, newInterval);
        std::cout << "Case " << testId++ << ": [";
        for (const auto &i : res) {
            std::cout << "[" << i.start << ", " << i.end << "], ";
        }
        std::cout << "]" << std::endl;
    }
}