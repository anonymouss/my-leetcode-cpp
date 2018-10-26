#!/bin/bash

## Update the completed progress at the bottom of README.md ##

# set manually by default
TOTAL=875 # actual number of algorithm problems, 875 @ 26th, Oct., 2018
SCALE=100

# count files in ./src/
COMPLETED=`ls src -l |grep "^-"|wc -l`

# update total number from shell input. otherwise use defalt value
if [ $# == 1 ]; then
    TOTAL=$1
fi

ACCURATE_RATE=`echo "($COMPLETED * $SCALE) / $TOTAL" | bc -l`

RATE=`printf "%.2f" $ACCURATE_RATE`
ARROWS=$(printf "%d" `echo "$ACCURATE_RATE+0.5" | bc`)
DASHES=`echo "100-$ARROWS" | bc`

STR_ARROWS=`printf "%-${ARROWS}s" ">"`
STR_DASHES=`printf "%-${DASHES}s" "-"`

function delete() {
    sed -i '/```/d' README.md
    sed -i '/Progress/d' README.md
    sed -i '/>-/d' README.md
}

function update() {
    echo "\`\`\`" >> README.md 
    echo "Progress: $RATE% finished. [$COMPLETED solved of total $TOTAL algorithm problems]" >> README.md
    echo "${STR_ARROWS// />}${STR_DASHES// /-}" >> README.md
    echo "\`\`\`" >> README.md 
}

delete
update

echo "progress updated to $RATE ($COMPLETED/$TOTAL)"