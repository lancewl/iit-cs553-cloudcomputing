#~/bin/bash
# call this with
# ~/hw3 $bash src/scripts/createfiles.sh

rm -rf data
mkdir data
cd data
# D1
mkdir D1; cd D1 
dd if=/dev/zero of=1 bs=1GB count=10
cd ../

# D2
mkdir D2; cd D2
dd if=/dev/zero of=1 bs=1GB count=5
dd if=/dev/zero of=2 bs=1GB count=5
cd ../

# D3
mkdir D3; cd D3
blocksize=500MB
n=5
for i in {1..4}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D4
mkdir D4; cd D4
blocksize=250MB
n=5
for i in {1..8}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D5
mkdir D5; cd D5
blocksize=833MB
n=1
for i in {1..8}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D6
mkdir D6; cd D6
blocksize=417MB
n=1
for i in {1..24}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D7
mkdir D7; cd D7
blocksize=208MB
n=1
for i in {1..48}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done

echo "done"
