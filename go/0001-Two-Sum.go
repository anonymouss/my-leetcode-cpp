package main

import "fmt"

func twoSum(nums []int, target int) []int {
	var m map[int]int = map[int]int{}
	for i, v := range nums {
		t := target - v
		if j, ok := m[t]; ok {
			return []int{i, j}
		}
		m[v] = i
	}
	return []int{-1, -1}
}

func main() {
	nums := []int{2, 7, 11, 15}
	target := 9

	result := twoSum(nums, target)

	fmt.Println(result)
}
