package main

import "fmt"

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	len1, len2 := len(nums1), len(nums2)
	totalLen := len1 + len2

	if totalLen%2 == 1 {
		return findKth(nums1, 0, len1, nums2, 0, len2, totalLen/2+1)
	} else {
		return (findKth(nums1, 0, len1, nums2, 0, len2, totalLen/2) +
			findKth(nums1, 0, len1, nums2, 0, len2, totalLen/2+1)) / 2.0
	}
}

func findKth(nums1 []int, start1 int, len1 int,
	nums2 []int, start2 int, len2 int, k int) float64 {
	if len1 > len2 {
		return findKth(nums2, start2, len2, nums1, start1, len1, k)
	} else if len1 == 0 {
		return float64(nums2[start2+k-1])
	} else if k == 1 {
		if nums1[start1] < nums2[start2] {
			return float64(nums1[start1])
		} else {
			return float64(nums2[start2])
		}
	}

	var div1 int
	if k/2 < len1 {
		div1 = k / 2
	} else {
		div1 = len1
	}
	div2 := k - div1

	if nums1[start1+div1-1] == nums2[start2+div2-1] {
		return float64(nums1[start1+div1-1])
	} else if nums1[start1+div1-1] < nums2[start2+div2-1] {
		return findKth(nums1, start1+div1, len1-div1,
			nums2, start2, len2, k-div1)
	} else {
		return findKth(nums1, start1, div1,
			nums2, start2+div2, len2-div2, k-div2)
	}
}

func main() {
	nums1 := []int{1, 3}
	nums2 := []int{2}

	fmt.Printf("Case 1: %v\n", findMedianSortedArrays(nums1, nums2))

	nums1 = []int{1, 2}
	nums2 = []int{3, 4}
	fmt.Printf("Case 2: %v\n", findMedianSortedArrays(nums1, nums2))
}
