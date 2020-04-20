#!/bin/bash
 
if [ $# -ne 2 ]
then
    echo "Usage: mySort_mon.sh [0 mySort | 1 Linux Sort] [dataset size in GB]"
    exit
fi

if [ $1 -eq 0 ]
then
    SORT = "./mySort gs.out 8"
    OUT = "monitor/mySort_$2G_mon"
elif [ $1 -eq 1 ]
then
    SORT = "sort -o sort.out gs.out"
    OUT = "monitor/LinuxSort_$2G_mon"
else
then
    echo "Wrong Sorting Mode. [0 mySort | 1 Linux Sort]"
    exit
fi

echo "Generating $2 GB dataset..."
gensort -a $((10000000*$2)) gs.out

echo "Sorting $2 GB dataset..."
pidstat -rudhI 1 -e ${SORT} > ${OUT}.log

echo "Validating sorted data..."
valsort sort.out

echo "Plotting performance graph..."
python3 monitor/plot.py ${OUT}.log ${OUT}.png

echo "removing the datasets"
rm gs.out sort.out
rm data/in_sorted*
