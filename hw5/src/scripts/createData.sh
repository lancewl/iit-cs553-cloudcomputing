#!/bin/bash

# make sure the gensort binary is in home dir. ~/gensort
# run this by ./src/scripts/createData.sh

rm -rf data

mkdir data
cd data
~/gensort -a $((10000000*1)) gs.out.1
# ~/gensort -a $((10000000*4)) gs.out.4
# ~/gensort -a $((10000000*8)) gs.out.8
# ~/gensort -a $((10000000*16)) gs.out.16

echo "gensort data done."