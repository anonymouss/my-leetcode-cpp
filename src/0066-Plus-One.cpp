/**
 * Given a non-empty array of digits representing a non-negative integer, plus one to the integer.
 * The digits are stored such that the most significant digit is at the head of the list, and each
 * element in the array contain a single digit.
 * You may assume the integer does not contain any leading zero, except the number 0 itself.
 *
 * Example 1:
 * Input: [1,2,3]
 * Output: [1,2,4]
 * Explanation: The array represents the integer 123.
 *
 * Example 2:
 * Input: [4,3,2,1]
 * Output: [4,3,2,2]
 * Explanation: The array represents the integer 4321.
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        if (digits.empty()) return digits;
        int carry = 1;
        for (int i = digits.size() - 1; i >= 0 && carry == 1; --i) {
            auto sum = digits[i] + carry;
            digits[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry == 1)
            digits.insert(digits.begin(), 1);
        return digits;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<vector<int>> inputs{
        {1, 2, 3},
        {4, 3, 2, 1},
        {9, 9, 9}
    };

    for (auto &input : inputs) {
        auto res = s.plusOne(input);
        std::cout << "Case " << testId++ << ": [";
        for (const auto &v : res) std::cout << v << ", ";
        std::cout << "]" << std::endl;
    }
}