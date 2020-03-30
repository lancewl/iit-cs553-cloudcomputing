#~/bin/bash
# call this with
# ~/hw3 $bash src/scripts/createfiles.sh

rm -rf data
mkdir data
cd data
mkdir 10G
cd 10G
# D1
mkdir D1; cd D1 
dd if=/dev/zero of=0 bs=1GB count=10
cd ../

# D2
mkdir D2; cd D2
dd if=/dev/zero of=0 bs=1GB count=5
dd if=/dev/zero of=1 bs=1GB count=5
cd ../

# D3
mkdir D3; cd D3
blocksize=500MB
n=5
for i in {0..3}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D4
mkdir D4; cd D4
blocksize=250MB
n=5
for i in {0..7}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D5
mkdir D5; cd D5
blocksize=833MB
n=1
for i in {0..11}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D6
mkdir D6; cd D6
blocksize=417MB
n=1
for i in {0..23}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D7
mkdir D7; cd D7
blocksize=208MB
n=1
for i in {0..47}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../
echo "10G done"
cd ../


# 1G
mkdir 1G
cd 1G
# D1
mkdir D1; cd D1 
dd if=/dev/zero of=0 bs=1GB count=1
cd ../

# D2
mkdir D2; cd D2
dd if=/dev/zero of=0 bs=500MB count=1
dd if=/dev/zero of=1 bs=500MB count=1
cd ../

# D3
mkdir D3; cd D3
blocksize=50MB
n=5
for i in {0..3}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D4
mkdir D4; cd D4
blocksize=25MB
n=5
for i in {0..7}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D5
mkdir D5; cd D5
blocksize=83MB
n=1
for i in {0..11}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D6
mkdir D6; cd D6
blocksize=41MB
n=1
for i in {0..23}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done
cd ../

# D7
mkdir D7; cd D7
blocksize=20MB
n=1
for i in {0..47}
do
    dd if=/dev/zero of=$i bs=$blocksize count=$n
done

echo "createfile.sh done"