/* 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。
假设输入的数组的任意两个数字都互不相同。

参考以下这颗二叉搜索树：
     5
    / \
   2   6
  / \
 1   3

示例 1：
输入: [1,6,3,2,5]
输出: false

示例 2：
输入: [1,3,2,6,5]
输出: true

提示：
数组长度 <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <queue>
#include <vector>
#include <stack>

#if 0
class Solution {
public:
    bool verifyPostorder(std::vector<int> &postorder) {
        order = &postorder;
        int size = order->size();
        return is_bst(size - 1, 0, size - 2);
    }

private:
    std::vector<int> *order;
    bool is_bst(int root_index, int range_from, int range_to) {
        if (range_from >= range_to) return true;
        auto i = range_from;
        while ((*order)[i] < (*order)[root_index]) ++i;
        for (auto j = i; j <= range_to; ++j) {
            if ((*order)[j] < (*order)[root_index]) return false;
        }

        return is_bst(root_index - 1, i, range_to - 1) && is_bst(i - 1, range_from, i - 2);
    }
};
#endif

class Solution {
public:
    bool verifyPostorder(std::vector<int> &postorder) {
        std::stack<int> stack;
        int root = INT32_MAX;
        for (int i = postorder.size() - 1; i >= 0; i--) {
            if (postorder[i] > root) return false;
            while (!stack.empty() && stack.top() > postorder[i]) {
                root = stack.top();
                stack.pop();
            }
            stack.push(postorder[i]);
        }
        return true;
    }
};

int main() {
    Solution s;

    std::vector<std::vector<int>> is{
        {1, 6, 3, 2, 5},
        {1, 3, 2, 6, 5}
    };

    for (auto &i : is) {
        std::cout << std::boolalpha << s.verifyPostorder(i) << std::endl;
    }
}