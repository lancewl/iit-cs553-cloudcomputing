#!/bin/bash
echo "Enter RR or RS or OPS"
read workload
echo "Enter the number of threads"
read concur

if [[ "$workload" == "RS" ]]
then 
    workload=1
    for record in 64k 1m 16m
    do
        iozone -T -I -i 0 -i $workload -s $(((10*1024)/concur))m -t $concur -r $record
    done
elif [[ "$workload" == "RR" ]]
then
    workload=2
    for record in 64k 1m 16m
    do
        iozone -T -I -i 0 -i $workload -s $(((10*1024)/concur))m -t $concur -r $record
    done
else
    for record in 64k 1m 16m
    do
        iozone -T -I -O -i 0 -i 2 -s $(((10*1024)/concur))m -t $concur -r $record
    done
fi