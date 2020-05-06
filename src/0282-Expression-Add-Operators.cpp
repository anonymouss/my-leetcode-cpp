/**
 * Given a string that contains only digits 0-9 and a target value, return all possibilities to add
 * binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.
 *
 * Example 1:
 * Input: num = "123", target = 6
 * Output: ["1+2+3", "1*2*3"] 
 *
 * Example 2:
 * Input: num = "232", target = 8
 * Output: ["2*3+2", "2+3*2"]
 *
 * Example 3:
 * Input: num = "105", target = 5
 * Output: ["1*0+5","10-5"]
 *
 * Example 4:
 * Input: num = "00", target = 0
 * Output: ["0+0", "0-0", "0*0"]
 *
 * Example 5:
 * Input: num = "3456237490", target = 9191
 * Output: []
 */

#include "MyMisc.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define LEETCODE_OFFICIAL_SOLUTION 0 // TLE
#define CPP_WORK 1
#define OPT_SOLUTION 2

#define COMPILE_VERSION OPT_SOLUTION

#if (COMPILE_VERSION == LEETCODE_OFFICIAL_SOLUTION)
class Solution {
public:
    std::vector<std::string> addOperators(std::string num, int target) {
        if (num.length() == 0) return {};
        mTarget = target;
        mDigits = num;
        mAnswer.clear();
        recurse(0, 0, 0, 0, {});
        return mAnswer;
    }

private:
    void recurse(uint32_t index, int64_t prevOp, int64_t curOp, int64_t value,
            std::vector<std::string> ops) {
        std::string nums = mDigits;
        if (index == nums.length()) {
            if (value == mTarget && curOp == 0) {
                std::string one;
                std::for_each(ops.begin() + 1, ops.end(), [&](const std::string &op) {
                    one += op;
                });
                mAnswer.emplace_back(one);
            }
            return;
        }

        curOp = curOp * 10 + (nums[index] - '0');
        std::string curVal = std::to_string(curOp);

        if (curOp > 0) {
            recurse(index + 1, prevOp, curOp, value, ops);
        }
        ops.emplace_back("+");
        ops.emplace_back(curVal);
        recurse(index + 1, curOp, 0, value + curOp, ops);
        ops.pop_back();
        ops.pop_back();

        if (ops.size() > 0) {
            ops.emplace_back("-");
            ops.emplace_back(curVal);
            recurse(index + 1, -curOp, 0, value - curOp, ops);
            ops.pop_back();
            ops.pop_back();

            ops.emplace_back("*");
            ops.emplace_back(curVal);
            recurse(index + 1, curOp * prevOp, 0, value - prevOp + (curOp * prevOp), ops);
            ops.pop_back();
            ops.pop_back();
        }
    }

    std::vector<std::string> mAnswer;
    std::string mDigits;
    int64_t mTarget;
};
#elif (COMPILE_VERSION == CPP_WORK)
class Solution {
public:
    std::vector<std::string> addOperators(std::string num, int target) {
        std::vector<std::string> result;
        std::string track{""};
        backtrack(num, target, 0, 0, 1, &result, &track);
        return result;
    }

private:
    void backtrack(const std::string &num, int64_t target, uint32_t index, int64_t value,
            int64_t mul, std::vector<std::string> *result, std::string *track) {
        if (index == num.length()) {
            if (value == target) {
                result->emplace_back(*track);
            }
            return;
        }
        auto len = track->size();
        for (auto i = index; i < num.length(); ++i) {
            auto val_str = num.substr(index, i - index + 1);
            auto n = stol(val_str);
            if (index == 0) {
                *track += val_str;
                backtrack(num, target, i + 1, n, n, result, track);
                track->resize(len);
            } else {
                *track += "+" + val_str;
                backtrack(num, target, i + 1, value + n, n, result, track);
                track->resize(len);
                *track += "-" + val_str;
                backtrack(num, target, i + 1, value - n, -n, result, track);
                track->resize(len);
                *track += "*" + val_str;
                backtrack(num, target, i + 1, value - mul + mul * n, mul * n, result, track);
                track->resize(len);
            }
            if (n == 0) {
                return;
            }
        }
    }
};
#elif (COMPILE_VERSION == OPT_SOLUTION)
class Solution {
public:
    std::vector<std::string> addOperators(std::string num, int target) {
        mNum = num;
        mTarget = target;
        std::vector<std::string> res;
        std::string expr(2 * num.length(), ' ');
        backtrack(&expr, 0, 0, 0, 0, &res);
        return res;
    }

private:
    void backtrack(std::string *expr, int len, int64_t prev, int64_t cur, uint32_t pos,
            std::vector<std::string> *res) {
        if (pos == mNum.length()) {
            if (cur == mTarget) {
                res->emplace_back(expr->substr(0, len));
            }
            return;
        }
        int64_t n = 0;
        auto s = pos;
        auto l = len;
        if (s != 0) ++len;
        while (pos < mNum.length()) {
            n = n * 10 + (mNum[pos] - '0');
            if (mNum[s] == '0' && pos - s > 0) {
                break;
            }
            (*expr)[len] = mNum[pos];
            ++len;
            ++pos;
            if (s == 0) {
                backtrack(expr, len, n, n, pos, res);
                continue;
            }
            (*expr)[l] = '+';
            backtrack(expr, len, n, cur + n, pos, res);
            (*expr)[l] = '-';
            backtrack(expr, len, -n, cur - n, pos, res);
            (*expr)[l] = '*';
            backtrack(expr, len, prev * n, cur - prev + prev * n, pos, res);
        }
    }

    std::string mNum;
    int64_t mTarget;
};
#endif

struct Input {
    std::string num;
    int target;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{"123", 6}, {"232", 8}, {"105", 5}, {"00", 0}, {"3456237490", 9191}};

    for (const auto &input : inputs) {
        TestCount();
        for (const auto &formula : sln.addOperators(input.num, input.target)) {
            std::cout << formula << std::endl;
        }
    }
}