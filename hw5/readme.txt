TODO: write me

# To create data files with gensort, first download the binary from http://www.ordinal.com/gensort.html
# run the script with
~/team-25/hw5$ ./src/scripts/createData.sh

# makefile needed.
# for now compile with
~/team-25/hw5$ g++ src/main.cpp src/io.cpp src/external_sort.cpp src/internal_sort.cpp -o main

# and run with
~/team-25/hw5$ ./main [inputFileName] [memSize] [debugFlag(0/1/2/3)]

e.g. ./main file.txt 8 0 // for normal run
     ./main file.txt 8 1 // for lance's branch
     ./main file.txt 8 2 // for kevin's branch

./main file.txt 8 4 // readChunk example. Make sure the file data/gs.out.test exists.
./main file.txt 8 5 // writeChunk example


# Add your test code in your specified if-branch (main.cpp: line 29)


# linux sort by ascii, run
LC_ALL=C sort data/gs.out.test