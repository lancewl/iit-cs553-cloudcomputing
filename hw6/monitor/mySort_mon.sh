#!/bin/bash
 
if [ $# -ne 2 ]
then
    echo "Usage: mySort_mon.sh [dataset size in GB] [output file name]"
    exit

echo "Generating $1 GB dataset..."
gensort -a $((10000000*$1)) gs.out

echo "Sorting $1 GB dataset..."
pidstat -rudh --human 1 -e ./mySort gs.out 8 0 > mySort_$1G_mon.log

rm gs.out sort.out