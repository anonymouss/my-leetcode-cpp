/**
 * 找出数组中重复的数字。
 * 
 * 在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字
 * 重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
 *
 * 示例 1：
 * 输入：
 * [2, 3, 1, 0, 2, 5, 3]
 * 输出：2 或 3 
 *
 * 限制：
 * 2 <= n <= 100000
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

#include <iostream>
#include <vector>
#include <unordered_set>

class Solution {
public:

    /**
     * 本题一个很直观的思路就是使用一个桶来存对应的元素，比如 std::set ，存之前只需要查看下对应的桶中是否
     * 已经有元素存在，有即为重复。但是本题有一个特殊的条件 “n个元素全部在0 ~ n-1的范围内”，则元素可以排序
     *  且下标不超过n，那无重复的情况则下标i存储的元素就是i。所以只要依次原地交换排序即可（同时比较需要交换
     * 的元素）
     */
    int findRepeatNumber(std::vector<int> &nums) {
        auto size = nums.size();
        for (auto i = 0; i < size; ++i) {
            while (nums[i] != i) {
                if (nums[nums[i]] == nums[i]) {
                    return nums[i];
                }
                auto tmp = nums[i];
                nums[i] = nums[tmp];
                nums[tmp] = tmp;
            }
        }
        return -1;
    }
};

#if 0
// legacy std::set solution
class Solution {
public:
    int findRepeatNumber(std::vector<int> &nums) {
        std::unordered_set<int> set;
        for (const auto &n : nums) {
            if (set.count(n)) {
                return n;
            }
            set.emplace(n);
        }
        return -1;
    }
};
#endif


int main() {
    Solution s;
    std::vector<int> input{2, 3, 1, 0, 2, 5, 3};

    std::cout << s.findRepeatNumber(input) << std::endl;
}