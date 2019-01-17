package main

import "fmt"

func lengthOfLongestSubstring(s string) int {
	pos := [256]int{}
	longest := 0
	lastRepeatPos := 0
	for i, c := range s {
		if pos[c] > lastRepeatPos {
			lastRepeatPos = pos[c]
		}
		distance := i - lastRepeatPos + 1
		if distance > longest {
			longest = distance
		}
		pos[c] = i + 1
	}
	return longest
}

func main() {
	s1 := "abcabcbb"
	s2 := "bbbbb"
	s3 := "pwwkew"

	fmt.Printf("Case 1 : %d\n", lengthOfLongestSubstring(s1))
	fmt.Printf("Case 2 : %d\n", lengthOfLongestSubstring(s2))
	fmt.Printf("Case 3 : %d\n", lengthOfLongestSubstring(s3))
}
