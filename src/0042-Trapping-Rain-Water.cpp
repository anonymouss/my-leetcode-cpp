/**
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it is able to trap after raining.
 * The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
 *
 * [Illustration](http://www.leetcode.com/static/images/problemset/rainwatertrap.png)
 *
 * In this case, 6 units of rain water (blue section) are being trapped. Thanks
 * Marcos for contributing this image!
 *
 * Example:
 * Input: [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 */

#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        int trapped = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        
        auto max = [](const int &a, const int &b) {
            return a > b ? a : b;
        };

        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (leftMax < rightMax) {
                trapped += leftMax - height[left];
                ++left;
            } else {
                trapped += rightMax - height[right];
                --right;
            }
        }

        return trapped;
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        stack<int> topPos;
        int trapped = 0;
        for (int i = 0; i < height.size(); ++i) {
            while (!topPos.empty() && height[i] > height[topPos.top()]) {
                int top = topPos.top();
                topPos.pop();
                if (topPos.empty()) break;
                int distancePos = i - topPos.top() - 1;
                int distanceHeight = (height[i] < height[topPos.top()] ?
                        height[i] : height[topPos.top()]) - height[top];
                trapped += distanceHeight * distancePos;
            }
            topPos.push(i);
        }
        return trapped;
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<int> height1{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    vector<int> height2{2, 0, 2};
    vector<int> height3{5, 4, 1, 2};
    vector<int> height4{5, 2, 1, 2, 1, 5};
    vector<int> height5{4, 2, 3};
    vector<int> height6{4, 2, 0, 3, 2, 5};

    auto exeTest = [&](vector<int> &height) {
        auto trapped = s.trap(height);
        std::cout << "Case " << testId++ << ": " << trapped << std::endl;
    };

    exeTest(height1);
    exeTest(height2);
    exeTest(height3);
    exeTest(height4);
    exeTest(height5);
    exeTest(height6);
}