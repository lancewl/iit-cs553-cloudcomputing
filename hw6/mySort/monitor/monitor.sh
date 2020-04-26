#!/bin/bash
 
if [ $# -ne 3 ]
then
    echo "Usage: mySort_mon.sh [0 mySort | 1 Linux Sort] [dataset size in GB] [memory size for sorting in GB]"
    exit
fi

if [ $1 -eq 0 ]
then
    SORT="./mySort gs.out $3"
    OUT="monitor/mySort_$2G_mon"
elif [ $1 -eq 1 ]
then
    SORT='sort -o sort.out gs.out'
    OUT="monitor/LinuxSort_$2G_mon"
else
    echo "Wrong Sorting Mode. [0 mySort | 1 Linux Sort]"
    exit
fi

echo "Generating $2 GB dataset..."
gensort -a $((10000000*$2)) gs.out

echo "Sorting $2 GB dataset..."
{ time pidstat -rudhI 1 -e ${SORT} > ${OUT}.log;} 2> ${OUT}.time

echo "Validating sorted data..."
valsort sort.out

echo "Plotting performance graph..."
python3 monitor/plot.py ${OUT}.log ${OUT}.png

echo "removing the datasets"
rm gs.out sort.out
if [ $1 -eq 0 ]
then
    rm data/in_sorted*
fi
