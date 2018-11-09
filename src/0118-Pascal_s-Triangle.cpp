/**
 * Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.
 * [image](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)
 * In Pascal's triangle, each number is the sum of the two numbers directly above it.
 *
 * Example:
 * Input: 5
 * Output:
 * [
 *      [1],
 *     [1,1],
 *    [1,2,1],
 *   [1,3,3,1],
 *  [1,4,6,4,1]
 * ]
 */

#include "../utils/MyMisc.h"
#include "../utils/MyContainerUtil.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        for (int i = 1; i <= numRows; ++i) {
            vector<int> row(i, 1);
            for (int j = 1; j < i-1; ++j) {
                auto last = res.back();
                row[j] = last[j] + last[j-1];
            }
            res.emplace_back(row);
        }
        return res;
    }
};

int main() {
    Solution s;

    vector<int> rows{5};

    for (auto &row : rows) {
        TestCount();
        auto res = s.generate(row);
        myDispVector2D(res);
    }
}