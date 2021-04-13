/* 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例 1:
输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
输出: 2

限制：
1 <= 数组长度 <= 50000

注意：本题与主站 169 题相同：https://leetcode-cn.com/problems/majority-element/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <cassert>

class Solution {
public:
    int majorityElement(std::vector<int> &nums) {
        int maj = 0, vote = 0;
        for (const auto &n : nums) {
            if (vote == 0) maj = n;
            vote += (n == maj ? 1 : -1);
        }
        return maj;
    }
};

struct Input {
    std::vector<int> nums;
    int ans;
};

int main() {
    Solution s;
    std::vector<Input> is{
        {{1, 2, 3, 2, 2, 2, 5, 4, 2}, 2}
    };

    for (auto &i : is) {
        assert(s.majorityElement(i.nums) == i.ans);
    }
}