#!/bin/sh

# Write a bash script to calculate the frequency of each word in a text file words.txt.
# For simplicity sake, you may assume:
# words.txt contains only lowercase characters and space ' ' characters.
# Each word must consist of lowercase characters only.
# Words are separated by one or more whitespace characters.
#
# Example:
# Assume that words.txt has the following content:
#
# the day is sunny the the
# the sunny is is
#
# Your script should output the following, sorted by descending frequency:
# the 4
# is 3
# sunny 2
# day 1
# Note:
# Don't worry about handling ties, it is guaranteed that each word's frequency count is unique.
# Could you write it in one-line using Unix pipes?

cat words.txt | xargs -n1 | awk '{
    if ($1 in dict) {
        dict[$1] += 1
    } else {
        dict[$1] = 1
    }
} END {
    for (word in dict) {
        print word, dict[word]
    }
}' | sort -rn -k2 | awk '{ print $1, $2 }'