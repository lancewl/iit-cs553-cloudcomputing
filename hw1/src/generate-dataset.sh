#!/usr/bin/env bash

# argument check
if [ "$#" -ne 2 ]; then
    echo "Usage: ./generate-dataset.sh [filename] [num_records]"
    exit 2
fi

FILENAME=$1
NUM_RECORDS=$2

rm -rf $FILENAME

count=0
while [ $count -lt $NUM_RECORDS ]
do
    count=$(($count+1))
    LINE="$RANDOM$RANDOM $RANDOM$RANDOM $(pwgen -s 100 1)"
    echo $LINE >> $FILENAME
done

echo "File created, filename - \"$FILENAME\" - ($NUM_RECORDS)"
