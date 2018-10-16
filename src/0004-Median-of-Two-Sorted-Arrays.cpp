/**
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 *
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 *
 * You may assume nums1 and nums2 cannot be both empty.
 *
 * Example 1:
 *
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * The median is 2.0
 *
 * Example 2:
 *
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 *
 * The median is (2 + 3)/2 = 2.5
 */

#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size(), totalLen = len1 + len2;


        if (totalLen % 2)
            return findKth(nums1, 0, len1, nums2, 0, len2, totalLen / 2 + 1);
        else
            return (findKth(nums1, 0, len1, nums2, 0, len2, totalLen / 2)
                    + findKth(nums1, 0, len1, nums2, 0, len2, totalLen / 2 + 1))
                    / 2.0;
    }

    double findKth(const vector<int> nums1, int start1, int len1,
                    const vector<int> nums2, int start2, int len2,
                    int k) {
        if (len1 > len2)
            return findKth(nums2, start2, len2, nums1, start1, len1, k);
        if (len1 == 0) return static_cast<double>(nums2[start2 + k - 1]);
        if (k == 1) return nums1[start1] < nums2[start2] ?
                        static_cast<double>(nums1[start1]) :
                        static_cast<double>(nums2[start2]);

        int div1 = k / 2 < len1 ? k / 2 : len1;
        int div2 = k - div1;

        if (nums1[start1 + div1 - 1] == nums2[start2 + div2 - 1])
            return static_cast<double>(nums1[start1 + div1 - 1]);
        if (nums1[start1 + div1 - 1] < nums2[start2 + div2 - 1]) {
            return findKth(nums1, start1 + div1, len1 - div1,
                            nums2, start2, len2, k - div1);
        } else {
            return findKth(nums1, start1, div1,
                            nums2, start2 + div2, len2 - div2, k - div2);
        }
    }
};

int main() {
    Solution s;
    vector<int> nums1, nums2;

    nums1 = {1, 3}, nums2 = {2};
    std::cout << "Case 1: "
                << s.findMedianSortedArrays(nums1, nums2) << std::endl;

    nums1 = {1, 2}, nums2 = {3, 4};
    std::cout << "Case 2: "
                << s.findMedianSortedArrays(nums1, nums2) << std::endl;
}