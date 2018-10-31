/**
 * Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?
 *
 * Example:
 * Input: 3
 * Output: 5
 * Explanation:
 * Given n = 3, there are a total of 5 unique BST's:
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 */

#include <iostream>
#include <vector>

using std::vector;

#define COMPILE_VERSION 2

#if (COMPILE_VERSION == 0)
// catalan number: (2n)! / ((n+1)!n!)
class Solution {
public:
    int numTrees(int n) {
        uint64_t cat = 1;
        for (int i = 0; i < n; ++i)
            cat = (4 * i + 2) * cat / (i + 2);
        return static_cast<int>(cat);
    }
};
#elif (COMPILE_VERSION == 1)
// TLE
class Solution {
public:
    int numTrees(int n) {
        if (n <= 1) return 1;
        int sum = 0;
        // iterating... choose node i+1 as root
        for (int i = 0; i < n; ++i)
            sum += numTrees(i) * numTrees(n-i-1);
        return sum;
    }
};
#elif (COMPILE_VERSION == 2)
// dp
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1, 0); 
        // 0, 1 -> 1
        dp[0] = 1; dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < i; ++j)
                dp[i] += dp[j] * dp[i-j-1];
        }
        return dp[n];
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<int> ns{1, 2, 3, 4, 19, 100};

    for (auto &n : ns) {
        if (n > 19) {
            std::cout << n << " overflow! input must < 19\n";
            return -1;
        }
        auto res = s.numTrees(n);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}