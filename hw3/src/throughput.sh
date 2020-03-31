#!/bin/bash

for workload in RS RR
do 
    if [[ "$workload" == "RS" ]]
    then 
        workload=1
    else
        workload=2
    fi
    
    for concur in 1 2 4 8 12 24 48
    do       
        for record in 64k 1m 16m
        do
            iozone -T -I -i 0 -i $workload -s $(((10*1024)/concur))m -t $concur -r $record
        done
    done 
    
done
  