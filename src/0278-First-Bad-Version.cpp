/**
 * You are a product manager and currently leading a team to develop a new product. Unfortunately,
 * the latest version of your product fails the quality check. Since each version is developed based
 * on the previous version, all the versions after a bad version are also bad.
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which
 * causes all the following ones to be bad.
 * You are given an API bool isBadVersion(version) which will return whether version is bad.
 * Implement a function to find the first bad version. You should minimize the number of calls to
 * the API.
 *
 * Example:
 * Given n = 5, and version = 4 is the first bad version.
 * call isBadVersion(3) -> false
 * call isBadVersion(5) -> true
 * call isBadVersion(4) -> true
 * Then 4 is the first bad version. 
 */

#include "MyMisc.h"

#include <iostream>
#include <vector>
#include <cassert>


int gAnswer = 0;
// Forward declaration of isBadVersion API.
bool isBadVersion(int version) {
    if (version >= gAnswer) {
        return true;
    } else {
        return false;
    }
}

class Solution {
public:
    int firstBadVersion(int n) {
        return firstBadVersion_l(1, n);
    }

private:
    int firstBadVersion_l(int start, int end) {
        if(start == end) return start;
        auto mid = start + (end - start) / 2;
        auto next = mid + 1;
        if (!isBadVersion(mid) && isBadVersion(next)) {
            return next;
        } else if (isBadVersion(mid)) {
            return firstBadVersion_l(start, mid);
        } else {
            return firstBadVersion_l(mid + 1, end);
        }
    }
};

struct Input {
    int n;
    int answer;
};

int main() {
    Solution sln;

    std::vector<Input> inputs{{5, 4}, {1, 1}};

    for (auto &input : inputs) {
        TestCount();
        gAnswer = input.answer;
        assert(sln.firstBadVersion(input.n) == gAnswer);
        
        std::cout << "OK, PASS!" << std::endl;
    }
}