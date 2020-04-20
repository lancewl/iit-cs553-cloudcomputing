#!/bin/bash
 
if [ $# -ne 2 ]
then
    echo "Usage: mySort_mon.sh [0 mySort | 1 Linux Sort] [dataset size in GB]"
    exit
fi

echo "Generating $2 GB dataset..."
gensort -a $((10000000*$2)) gs.out

if [ $1 -eq 0 ]
then
    OUT = "monitor/mySort_$2G_mon"
    echo "Sorting $2 GB dataset by mySort..."
    pidstat -rudhI 1 -e  ./mySort gs.out 8 > ${OUT}.log
elif [ $1 -eq 1 ]
then
    OUT = "monitor/LinuxSort_$2G_mon"
    echo "Sorting $2 GB dataset by Linux Sort..."
    pidstat -rudhI 1 -e  sort -o sort.out gs.out > ${OUT}.log
else
    echo "Wrong Sorting Mode. [0 mySort | 1 Linux Sort]"
    rm gs.out
    exit
fi

echo "Validating sorted data..."
valsort sort.out

echo "Plotting performance graph..."
python3 monitor/plot.py ${OUT}.log ${OUT}.png

echo "removing the datasets"
rm gs.out sort.out
rm data/in_sorted*
