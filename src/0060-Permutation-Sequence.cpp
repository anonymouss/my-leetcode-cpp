/**
 * The set [1,2,3,...,n] contains a total of n! unique permutations.
 * By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
 * "123"
 * "132"
 * "213"
 * "231"
 * "312"
 * "321"
 *
 * Given n and k, return the kth permutation sequence.
 * Note:
 *  - Given n will be between 1 and 9 inclusive.
 *  - Given k will be between 1 and n! inclusive.
 *
 * Example 1:
 * Input: n = 3, k = 3
 * Output: "213"
 *
 * Example 2:
 * Input: n = 4, k = 9
 * Output: "2314"
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::swap;
using std::next_permutation;

#define COMPILE_VERSION 1

#if (COMPILE_VERSION == 0)
// brute force
class Solution {
public:
    string getPermutation(int n, int k) {
        string s{""};
        for (int i = 1; i <= n; ++i) s += ('0' + i);

        while (--k > 0)
            nextPermutation(s);
        return s;
    }

    void nextPermutation(string &s) {
        for (int i = s.length() - 1; i > 0; --i) {
            if (s[i] > s[i - 1]) {
                for (int j = s.length() - 1; j >= i; --j) {
                    if (s[j] > s[i - 1]) {
                        swap(s[i - 1], s[j]);
                        break;
                    }
                }
                int l = i, r = s.length() - 1;
                while (l <= r) {
                    swap(s[l], s[r]);
                    ++l; --r;
                }
                break;
            }
        }
    }
};
#elif (COMPILE_VERSION == 1)
class Solution {
public:
    // find kth permutation directly
    // suppose n = 3, k = 3, all permutations are:
    // [1, [2, 3]]
    // [1, [3, 2]]
    // [2, [1, 3]]
    // [2, [3, 1]]
    // [3, [1, 2]]
    // [3, [2, 1]]
    // fristly, find the first number.
    // k = 3 = 2 + 1 = 2! + 1!
    // 2! means total permutation counts of n = 2
    // k = 3 contains one 2!
    // so first number is 2 (3 / 2 = 1)
    // remove 2 from (1, 2, 3)... got (1, 3)
    // then find 3 % 2 = 1's permutation of (1, 3)
    // do recursion.
    string getPermutation(int n, int k) {
        string s{""}, res{""};
        for (int i = 1; i <= n; ++i) s += (i + '0');

        vector<int> factorial(10, 1);
        for (int i = 1; i <= 9; ++i)
            factorial[i] = factorial[i - 1] * i;

        k = k - 1;
        while (n != 0) {
            int idx = k / factorial[n - 1];
            k = k % factorial[n - 1];
            --n;
            res += s[idx];
            s.erase(idx, 1);
        }
        return res;
    }
};
#elif (COMPILE_VERSION == 2)
class Solution {
public:
    // cheat... use STL
    string getPermutation(int n, int k) {
        string s{""};
        for (int i = 1; i <= n; ++i) s += ('0' + i);
        for (int i = 1; i < k; ++i)
            next_permutation(s.begin(), s.end());
        return s;
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> nks{
        // n, k
        {3, 3},
        {4, 9},
        {0, 1}
    };

    for (const auto &nk : nks) {
        auto res = s.getPermutation(nk[0], nk[1]);
        std::cout << "Case " << testId++ << ": " << res << std::endl;
    }
}