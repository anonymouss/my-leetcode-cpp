/* 我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。

示例:
输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
说明:  
1 是丑数。
n 不超过1690。
注意：本题与主站 264 题相同：https://leetcode-cn.com/problems/ugly-number-ii/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/chou-shu-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int nthUglyNumber(int n) {
        int a = 0, b = 0, c = 0;
        std::vector<int> dp(n);
        dp[0] = 1;
        for (auto i = 1; i < n; ++i) {
            auto n2 = 2 * dp[a], n3 = 3 * dp[b], n5 = 5 * dp[c];
            dp[i] = std::min(std::min(n2, n3), n5);
            if (dp[i] == n2) ++a;
            if (dp[i] == n3) ++b;
            if (dp[i] == n5) ++c;
        }
        return dp[n - 1];
    }
};

int main() {
    Solution s;

    std::vector<int> ns{10};
    for (const auto &n : ns) {
        std::cout << s.nthUglyNumber(n) << std::endl;
    }
}