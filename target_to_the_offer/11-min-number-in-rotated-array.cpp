/* 
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数
组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  

示例 1：
输入：[3,4,5,1,2]
输出：1

示例 2：
输入：[2,2,2,0,1]
输出：0 */

#include <iostream>
#include <vector>

class Solution {
public:
    int minArray(std::vector<int> &numbers) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) {
            auto m = (l + r) / 2;
            if (numbers[m] > numbers[r]) {
                l = m + 1;
            } else if (numbers[m] < numbers[r]) {
                r = m; // 不能减，m 可能就是最小
            } else {
                --r; // 相等肯定是右边存在重复数字
            }
        }
        return numbers[r];
    }
};

int main() {
    Solution s;
    std::vector<std::vector<int>> inputs{
        {3, 4, 5, 1, 2},
        {2, 2, 2, 0, 1},
        {1, 3, 3},
        {3, 1, 1}
    };
    
    for (auto &numbers : inputs) {
        std::cout << s.minArray(numbers) << std::endl;
    }
}