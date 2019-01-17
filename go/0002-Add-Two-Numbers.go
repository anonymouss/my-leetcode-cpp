package main

import (
	"./util"
)

type ListNode = util.ListNode

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	pHead := &ListNode{-1, nil}
	pCurrent := pHead
	carry := 0
	for l1 != nil || l2 != nil || carry != 0 {
		op1, op2 := 0, 0
		if l1 != nil {
			op1 = l1.Val
			l1 = l1.Next
		}
		if l2 != nil {
			op2 = l2.Val
			l2 = l2.Next
		}
		sum := op1 + op2 + carry
		carry = sum / 10
		pNode := &ListNode{sum % 10, nil}
		pCurrent.Next = pNode
		pCurrent = pNode
	}
	return pHead.Next
}

func main() {
	nums1 := []int{2, 4, 3}
	nums2 := []int{5, 6, 4}

	list1 := util.GenerateList(nums1)
	list2 := util.GenerateList(nums2)

	result := addTwoNumbers(list1, list2)

	util.DisplayList(result)
}
