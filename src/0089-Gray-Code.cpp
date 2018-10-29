/**
 * The gray code is a binary numeral system where two successive values differ in only one bit.
 * Given a non-negative integer n representing the total number of bits in the code, print the
 * sequence of gray code. A gray code sequence must begin with 0.
 *
 * Example 1:
 * Input: 2
 * Output: [0,1,3,2]
 * Explanation:
 * 00 - 0
 * 01 - 1
 * 11 - 3
 * 10 - 2
 *
 * For a given n, a gray code sequence may not be uniquely defined.
 * For example, [0,2,3,1] is also a valid gray code sequence.
 * 00 - 0
 * 10 - 2
 * 11 - 3
 * 01 - 1
 *
 * Example 2:
 * Input: 0
 * Output: [0]
 * Explanation: We define the gray code sequence to begin with 0.
 *              A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
 *              Therefore, for n = 0 the gray code sequence is [0].
 */

#include <iostream>
#include <vector>
#include <bitset>

using std::vector;

#define COMPILE_VERSION 1

// https://en.wikipedia.org/wiki/Gray_code
// binary to gray
#if (COMPILE_VERSION == 0)
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> gray;
        int exp = 1;
        for (int i = 0; i < n; ++i) exp <<= 1;
        for (int i = 0; i < exp; ++i)
            gray.emplace_back((i>>1)^i);
        return gray;
    }
};
#elif (COMPILE_VERSION == 1)
// binary reflection
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int>gray;
        gray.emplace_back(0);
        
        for(int i = 0; i < n; i++){
            int size = gray.size();
            // add 1 to reflection in high bit, also keep un-reflected vals unchanged
            for(int k = size - 1; k >= 0; k--){
                gray.emplace_back(gray[k] | 1 << i);
            }
        }
        return gray;
    }
};
#endif

int main() {
    Solution s;
    int testId = 1;

    vector<int> ns{2, 0};

    for (auto &n : ns) {
        auto res = s.grayCode(n);
        std::cout << "Case " << testId++ << ": ";
        for (const auto &e : res) std::cout << e << ", ";
        std::cout << std::endl;
    }
}