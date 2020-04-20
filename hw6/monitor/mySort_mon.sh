#!/bin/bash
 
if [ $# -ne 1 ]
then
    echo "Usage: mySort_mon.sh [dataset size in GB]"
    exit
fi

echo "Generating $1 GB dataset..."
gensort -a $((10000000*$1)) gs.out

echo "Sorting $1 GB dataset..."
pidstat -rudhI 1 -e ./mySort gs.out 8 > monitor/mySort_$1G_mon.log

echo "Validating sorted data..."
valsort sort.out

echo "Plotting performance graph..."
python3 monitor/plot.py monitor/mySort_$1G_mon.log monitor/mySort_$1G_mon.png

echo "removing the datasets"
rm gs.out sort.out
rm data/in_sorted*
