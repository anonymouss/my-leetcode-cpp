package util

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

func GenerateList(nums []int) *ListNode {
	pHead := &ListNode{0, nil}
	pTmp := pHead
	for _, val := range nums {
		pNode := &ListNode{val, nil}
		pTmp.Next = pNode
		pTmp = pNode
	}
	return pHead.Next
}

func DisplayList(list *ListNode) {
	for l := list; l != nil; l = l.Next {
		fmt.Printf("%v, ", l.Val)
	}
	fmt.Println()
}
