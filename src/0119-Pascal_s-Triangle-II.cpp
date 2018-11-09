/**
 * Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.
 * Note that the row index starts from 0.
 * In Pascal's triangle, each number is the sum of the two numbers directly above it.
 *
 * Example:
 * Input: 3
 * Output: [1,3,3,1]
 * Follow up:
 * Could you optimize your algorithm to use only O(k) extra space?
 */

#include "../utils/MyMisc.h"
#include "../utils/MyContainerUtil.h"

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        ++rowIndex;
        vector<int> res(rowIndex, 1);
        for (int i = 3; i <= rowIndex; ++i) {
            int pre = res[0];
            for (int j = 1; j <i -1; ++j) {
                int cur = res[j];
                res[j] = cur + pre;
                pre = cur;
            }
        }
        return res;
    }
};

int main() {
    Solution s;

    vector<int> indexes{0, 3, 5};

    for (auto &index : indexes) {
        auto res = s.getRow(index);
        myDispVector1D(res);
    }
}