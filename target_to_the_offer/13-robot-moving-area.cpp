/* 地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，
它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。
例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。
请问该机器人能够到达多少个格子？

示例 1：
输入：m = 2, n = 3, k = 1
输出：3

示例 2：
输入：m = 3, n = 1, k = 0
输出：1

提示：
1 <= n,m <= 100
0 <= k <= 20

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#include <iostream>
#include <vector>
#include <queue>

#if 0
// dfs
class Solution {
public:
    int movingCount(int _m, int _n, int _k) {
        m = _m;
        n = _n;
        k = _k;
        visited.clear();
        for (auto i = 0; i < m; ++i) {
            visited.emplace_back(std::vector<char>(n, 'N'));
        }
        return dfs(0, 0, 0, 0);
    }

private:
    int m;
    int n;
    int k;
    std::vector<std::vector<char>> visited;

    int calc(int x, int sum) {
        return (x + 1) % 10 != 0 ? sum + 1 : sum - 8;
    }

    int dfs(int im, int in, int sum_m, int sum_n) {
        if (sum_m + sum_n > k || im >= m || in >= n || visited[im][in] == 'Y') {
            return 0;
        }
        visited[im][in] = 'Y';

        return 1 + dfs(im + 1, in, calc(im, sum_m), sum_n)
                + dfs(im, in + 1, sum_m, calc(in, sum_n));
    }
};
#endif

// bfs
class Solution {
public:
    int movingCount(int m, int n, int k) {
        std::vector<std::vector<char>> visited(m, std::vector<char>(n, 'N'));
        int count = 0;
        std::queue<std::vector<int>> queue;
        queue.push({0, 0, 0, 0});
        while (queue.size() > 0) {
            auto e = queue.front(); 
            queue.pop();
            int im = e[0], in = e[1], sum_m = e[2], sum_n = e[3];
            if (sum_m + sum_n > k || im >= m || in >= n || visited[im][in] == 'Y') {
                continue;
            }
            visited[im][in] = 'Y';
            ++count;
            queue.push({im + 1, in, calc(im, sum_m), sum_n});
            queue.push({im, in + 1, sum_m, calc(in, sum_n)});
        }
        return count;
    }

private:
    int calc(int x, int sum) {
        return (x + 1) % 10 != 0 ? sum + 1 : sum - 8;
    }
};

struct Input {
    int m;
    int n;
    int k;
};

int main() {
    Solution s;
    std::vector<Input> inputs{{2, 3, 1}, {3, 1, 0}, {1, 2, 1}};

    for (const auto &i : inputs) {
        std::cout << s.movingCount(i.m, i.n, i.k) << std::endl;
    }
}