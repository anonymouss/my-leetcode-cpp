/**
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 *
 * An input string is valid if:
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * Note that an empty string is also considered valid.
 *
 * Example 1:
 * Input: "()"
 * Output: true
 *
 * Example 2:
 * Input: "()[]{}"
 * Output: true
 *
 * Example 3:
 * Input: "(]"
 * Output: false
 *
 * Example 4:
 * Input: "([)]"
 * Output: false
 *
 * Example 5:
 * Input: "{[]}"
 * Output: true
 */

#include <iostream>
#include <string>
#include <stack>

using std::string;
using std::stack;

class Solution {
public:
    bool isValid(string s) {
        if (s.empty()) return true;
        stack<char> stk;
        for (const auto &c : s) {
            if (c == '(' || c == '{' || c == '[') {
                stk.push(c);
            } else if (!stk.empty() && isPaired(stk.top(), c)) {
                stk.pop();
            } else {
                return false;
            }
        }
        return stk.empty();
    }

    bool isPaired(const char &left, const char &right) {
        switch (left) {
            case '(': return right == ')';
            case '{': return right == '}';
            case '[': return right == ']';
            default: return false;
        }
    }
};

int main() {
    Solution s;

    string s1{"()"};        // expect true
    string s2{"()[]{}"};    // expect true
    string s3{"(]"};        // expect false
    string s4{"([)]"};      // expect false
    string s5{"{[]}"};      // expect true
    string s6{"("};         // expect false
    string s7{"(("};        // expect false

    std::cout << std::boolalpha;
    std::cout << "Case 1: " << s.isValid(s1) << std::endl;
    std::cout << "Case 2: " << s.isValid(s2) << std::endl;
    std::cout << "Case 3: " << s.isValid(s3) << std::endl;
    std::cout << "Case 4: " << s.isValid(s4) << std::endl;
    std::cout << "Case 5: " << s.isValid(s5) << std::endl;
    std::cout << "Case 6: " << s.isValid(s6) << std::endl;
    std::cout << "Case 7: " << s.isValid(s7) << std::endl;
}