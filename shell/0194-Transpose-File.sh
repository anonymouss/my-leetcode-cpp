#!/bin/sh

# Given a text file file.txt, transpose its content.
# You may assume that each row has the same number of columns and each field is separated by the ' ' character.
# Example:
# If file.txt has the following content:
# name age
# alice 21
# ryan 30
# Output the following:
# name alice ryan
# age 21 30

cat file_.txt | awk '{
    for (field = 1; field <= NF; field += 1) {
        if (NR == 1) {
            data[field] = $field
        } else {
            data[field] = data[field] " " $field
        }
    }
} END {
    for (i in data) {
        print data[i]
    }
}'