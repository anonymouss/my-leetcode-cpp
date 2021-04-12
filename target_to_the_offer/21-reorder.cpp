/* 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，
所有偶数位于数组的后半部分。

示例：
输入：nums = [1,2,3,4]
输出：[1,3,2,4] 
注：[3,1,2,4] 也是正确的答案之一。
 
提示：
0 <= nums.length <= 50000
1 <= nums[i] <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<int> exchange(std::vector<int> &nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            if (nums[l] % 2 == 1) {
                ++l;
                continue;
            }
            if (nums[r] % 2 == 0) {
                --r;
                continue;
            }
            std::swap(nums[l], nums[r]);
            ++l;
            --r;
        }

        return nums;
    }
};

int main() {
    Solution s;

    std::vector<std::vector<int>> nums{
        {1, 2, 3, 4},
        {}
    };

    auto print_v = [](const std::vector<int> &v) {
        for (const auto &e : v) {
            std::cout << e << ", ";
        }
        std::cout << std::endl;
    };

    for (auto &n : nums) {
        print_v(s.exchange(n));
    }
}