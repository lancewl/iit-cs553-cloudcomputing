#!/bin/bash

# make sure the gensort binary is in home dir. ~/gensort
# run this by ./src/scripts/createData.sh

rm -rf data

mkdir data
cd data
~/gensort -a $((10000000*1)) gs.out.1g
~/gensort -a $((10000000*4)) gs.out.4g
~/gensort -a $((10000000*16)) gs.out.16g
~/gensort -a $((10000000*64)) gs.out.8g

echo "gensort data done."