#!/bin/bash

for workload in RS RR
    do 
    if [["$workload" -eq "RS"]]
    then 
    workload=1
    else [["$workload" -eq "RR"]]
    workload=2
    fi
    
    for concur in 1 2 4 8 12 24 48
        do       
        for record in 64k 1m 16m
            do
            len= bc -l <<< 'scale=2; 100/concur'
            iozone -T -I -i 0 -i $workload -s $((10000/concur))m -t $concur -r $record
            done
        done 
    done
  