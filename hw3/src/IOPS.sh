#!/bin/bash

for concur in 1 2 4 8 12 24 48
do       
    for record in 64k 1m 16m
    do
        iozone -T -I -O -i 0 -i 2 -s $((10000/concur))m -t $concur -r $record
    done
done 