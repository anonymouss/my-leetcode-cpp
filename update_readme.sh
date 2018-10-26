#!/bin/bash

# set manually by default
TOTAL=875 # actual number of algorithm problems
COMPLETED=75
SCALE=100

# receive completed num from shell
if [ $# == 1 ]; then
    COMPLETED=$1
# receive completed & total num from shell
elif [ $# == 2 ]; then
    COMPLETED=$1
    TOTAL=$2
fi

ACCURATE_RATE=`echo "($COMPLETED * $SCALE) / $TOTAL" | bc -l`

RATE=`printf "%.2f" $ACCURATE_RATE`
ARROWS=$(printf "%d" `echo "$ACCURATE_RATE+0.5" | bc`)
STARS=`echo "100-$ARROWS" | bc`

STR_ARROWS=`printf "%-${ARROWS}s" ">"`
STR_DASHES=`printf "%-${STARS}s" "-"`

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

echo "progress updated to $RATE"