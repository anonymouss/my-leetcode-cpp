/* 输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，
则最小的4个数字是1、2、3、4。

示例 1：
输入：arr = [3,2,1], k = 2
输出：[1,2] 或者 [2,1]

示例 2：
输入：arr = [0,1,2,1], k = 1
输出：[0]

限制：
0 <= k <= arr.length <= 10000
0 <= arr[i] <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
    std::vector<int> getLeastNumbers(std::vector<int> &arr, int k) {
        if (k == 0) return {};
        std::vector<int> res;
        std::priority_queue<int> queue;
        for (auto i = 0; i < k; ++i) queue.emplace(arr[i]);
        for (auto i = k; i < arr.size(); ++i) {
            if (arr[i] < queue.top()) {
                queue.pop();
                queue.emplace(arr[i]);
            }
        }
        while (!queue.empty()) {
            res.emplace_back(queue.top());
            queue.pop();
        }
        return res;
    }
};

struct Input {
    std::vector<int> arr;
    int k;
};

int main() {
    Solution s;
    std::vector<Input> is{
        {{3, 2, 1}, 2},
        {{0, 1, 2, 1}, 1},
        {{0,0,0,2,0,5}, 0}
    };

    auto print_v = [](const std::vector<int> &iv) {
        for (const auto &i : iv) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    };

    for (auto &i : is) {
        print_v(s.getLeastNumbers(i.arr, i.k));
    }
}