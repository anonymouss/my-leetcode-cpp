/* 
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100"、"5e2"、"-123"、"3.1416"、
"-1E-16"、"0123"都表示数值，但"12e"、"1a3.14"、"1.2.3"、"+-5"及"12e+5.4"都不是。 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cstdint>
#include <unordered_map>
#include <map>

class Solution {
public:
    bool isNumber(std::string s) {
        std::map<State, std::map<Type, State>> transfer{
            {
                STATE_INIT, {
                    {TYPE_SPACE,        STATE_INIT},
                    {TYPE_SIGN,         STATE_SIGN_INT},
                    {TYPE_DIGIT,        STATE_INT},
                    {TYPE_POINT,        STATE_POINT_NON}
                }
            },
            {
                STATE_SIGN_INT, {
                    {TYPE_DIGIT,        STATE_INT},
                    {TYPE_POINT,        STATE_POINT_NON}
                }
            },
            {
                STATE_INT, {
                    {TYPE_DIGIT,        STATE_INT},
                    {TYPE_EXP,          STATE_EXP},
                    {TYPE_POINT,        STATE_POINT_INT},
                    {TYPE_SPACE,        STATE_END}
                }
            },
            {
                STATE_POINT_INT, {
                    {TYPE_DIGIT,        STATE_FRAC},
                    {TYPE_EXP,          STATE_EXP},
                    {TYPE_SPACE,        STATE_END}
                }
            },
            {
                STATE_POINT_NON, {
                    {TYPE_DIGIT,        STATE_FRAC}
                }
            },
            {
                STATE_FRAC, {
                    {TYPE_DIGIT,        STATE_FRAC},
                    {TYPE_EXP,          STATE_EXP},
                    {TYPE_SPACE,        STATE_END}
                }
            },
            {
                STATE_EXP,  {
                    {TYPE_DIGIT,        STATE_EXP_NUM},
                    {TYPE_SIGN,         STATE_SIGN_EXP}
                }
            },
            {
                STATE_SIGN_EXP, {
                    {TYPE_DIGIT,        STATE_EXP_NUM}
                }
            },
            {
                STATE_EXP_NUM, {
                    {TYPE_DIGIT,        STATE_EXP_NUM},
                    {TYPE_SPACE,        STATE_END}
                }
            },
            {
                STATE_END, {
                    {TYPE_SPACE,        STATE_END}
                }
            }
        };

        auto size = s.length();
        State state = STATE_INIT;
        for (const auto &c : s) {
            auto type = getType(c);
            if (transfer[state].count(type) == 0) {
                return false;
            } else {
                state = transfer[state][type];
            }
        }
        return state == STATE_INT || state == STATE_POINT_INT || state == STATE_FRAC
                || state == STATE_EXP_NUM || state == STATE_END;
    }

private:
    enum State : uint32_t {
        STATE_INIT,             // 初始状态
        STATE_SIGN_INT,         // 整数前符号位
        STATE_INT,              // 整数部分
        STATE_POINT_INT,        // 小数点（整数在前）
        STATE_POINT_NON,        // 小数点（无整数在前）
        STATE_FRAC,             // 小数部分
        STATE_EXP,              // 指数符号
        STATE_SIGN_EXP,         // 指数后符号位
        STATE_EXP_NUM,          // 指数数值部分
        STATE_END,
    };

    enum Type : uint32_t {
        TYPE_DIGIT,
        TYPE_SIGN,
        TYPE_POINT,
        TYPE_EXP,
        TYPE_SPACE,
        TYPE_ILL,
    };

    Type getType(const char &c) {
        if (c >= '0' && c <= '9') {
            return TYPE_DIGIT;
        } else if (c == '+' || c == '-') {
            return TYPE_SIGN;
        } else if (c == '.') {
            return TYPE_POINT;
        } else if (c == 'e' || c == 'E') {
            return TYPE_EXP;
        } else if (c == ' ') {
            return TYPE_SPACE;
        } else {
            return TYPE_ILL;
        }
    }
};

int main() {
    Solution sl;

    std::vector<std::string> ss{"+100", "5e2", "-123", "3.1416", "-1E-16", "0123", "12e", "1a3.14",
            "1.2.3", "+-5", "12e+5.4"};
    for (const auto &s : ss) {
        std::cout << std::boolalpha << sl.isNumber(s) << std::endl;
    }
}