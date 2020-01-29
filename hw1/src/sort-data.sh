#!/usr/bin/env bash

# argument check
if [ "$#" -ne 2 ]; then
    echo "Usage: ./sort-data.sh [inputfile] [outpufile]"
    exit 2
fi

INPUT=$1
OUTPUT=$2

sort -n $INPUT > $OUTPUT

echo "Finish sorting. Outputfile - "$OUTPUT
