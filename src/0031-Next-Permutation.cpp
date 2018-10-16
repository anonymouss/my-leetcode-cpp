/**
 * Implement next permutation, which rearranges numbers into the
 * lexicographically next greater permutation of numbers.
 *
 * If such arrangement is not possible, it must rearrange it as the lowest
 * possible order (ie, sorted in ascending order).
 *
 * The replacement must be in-place and use only constant extra memory.
 *
 * Here are some examples. Inputs are in the left-hand column and its
 * corresponding outputs are in the right-hand column.
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1
 */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.empty()) return;
        int maxIdx = nums.size() - 1;
        for (int idx = maxIdx; idx > 0; --idx) {
            if (nums[idx] > nums[idx -1]) {
                int i = maxIdx;
                while (nums[i] <= nums[idx - 1]) --i;
                auto val = nums[i];
                nums[i] = nums[idx - 1];
                nums[idx - 1] = val;
                int l = idx, r = maxIdx;
                while (l < r) {
                    auto t = nums[l];
                    nums[l] = nums[r];
                    nums[r] = t;
                    ++l, --r;
                }
                return;
            }
        }
        sort(nums.begin(), nums.end());
    }
};

int main() {
    Solution s;
    static int testId = 1;

    vector<int> input1{1, 2, 3};
    vector<int> input2{3, 2, 1};
    vector<int> input3{1, 1, 5};
    vector<int> input4{1, 3, 2};

    auto dispVec = [](const vector<int> &vec) {
        for (const auto &v : vec)
            std::cout << v << ", ";
    };

    auto exeTest = [&](vector<int> &nums) {
        std::cout << "Case " << testId << ": ";
        dispVec(nums);
        std::cout << " -- next ->  ";
        s.nextPermutation(nums);
        dispVec(nums);
        std::cout << std::endl;
        ++testId;
    };

    exeTest(input1);
    exeTest(input2);
    exeTest(input3);
    exeTest(input4);
}