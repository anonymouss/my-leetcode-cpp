/**
 * Compare two version numbers version1 and version2.
 * If version1 > version2 return 1; if version1 < version2 return -1;otherwise return 0.
 * You may assume that the version strings are non-empty and contain only digits and the .
 * character. The . character does not represent a decimal point and is used to separate number
 * sequences. For instance, 2.5 is not "two and a half" or "half way to version three", it is the
 * fifth second-level revision of the second first-level revision. You may assume the default
 * revision number for each level of a version number to be 0. For example, version number 3.4 has a
 * revision number of 3 and 4 for its first and second level revision number. Its third and fourth
 * level revision number are both 0.
 *
 * Example 1:
 * Input: version1 = "0.1", version2 = "1.1"
 * Output: -1
 *
 * Example 2:
 * Input: version1 = "1.0.1", version2 = "1"
 * Output: 1
 *
 * Example 3:
 * Input: version1 = "7.5.2.4", version2 = "7.5.3"
 * Output: -1
 *
 * Example 4:
 * Input: version1 = "1.01", version2 = "1.001"
 * Output: 0
 * Explanation: Ignoring leading zeroes, both “01” and “001" represent the same number “1”
 *
 * Example 5:
 * Input: version1 = "1.0", version2 = "1.0.0"
 * Output: 0
 * Explanation: The first version number does not have a third level revision number, which means
 * its third level revision number is default to "0"  
 *
 * Note:
 * Version strings are composed of numeric strings separated by dots . and this numeric strings may
 * have leading zeroes. Version strings do not start or end with dots, and they will not be two
 * consecutive dots.
 */

#include "MyMisc.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int compareVersion(std::string version1, std::string version2) {
        std::vector<int> v1;
        std::vector<int> v2;
        std::size_t start1 = 0, start2 = 0;
        std::size_t pos1 = 0, pos2 = 0;
        while ((pos1 = version1.find(".", start1)) != std::string::npos) {
            v1.emplace_back(std::stoi(version1.substr(start1, pos1 - start1)));
            start1 = pos1 + 1;
        }
        v1.emplace_back(std::stoi(version1.substr(start1)));
        while ((pos2 = version2.find(".", start2)) != std::string::npos) {
            v2.emplace_back(std::stoi(version2.substr(start2, pos2 - start2)));
            start2 = pos2 + 1;
        }
        v2.emplace_back(std::stoi(version2.substr(start2)));
        auto l1 = v1.size(), l2 = v2.size();
        auto lmin = std::min(l1, l2);
        for (auto i = 0; i < lmin; ++i) {
            if (v1[i] > v2[i])
                return 1;
            else if (v1[i] < v2[i])
                return -1;
        }

        if (l1 > lmin) {
            for (auto i = lmin; i < l1; ++i) {
                if (v1[i] > 0) return 1;
            }
        } else if (l2 > lmin) {
            for (auto i = lmin; i < l2; ++i) {
                if (v2[i] > 0) return -1;
            }
        }

        return 0;
    }
};

int main() {
    Solution sln;
    std::vector<std::string> version1{"0.1", "1.0.1", "7.5.2.4", "1.01", "1.0"};
    std::vector<std::string> version2{"1.1", "1", "7.5.3", "1.001", "1.0.0"};

    for (auto i = 0; i < version1.size(); ++i) {
        TestCount();
        std::cout << sln.compareVersion(version1[i], version2[i]) << std::endl;
    }
}