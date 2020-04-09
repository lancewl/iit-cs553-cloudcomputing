TODO: write me

# To create data files with gensort, first download the binary from http://www.ordinal.com/gensort.html
# and run the script with
~/team-25/hw5$ ./src/scripts/createData.sh

# for now compile with
~/team-25/hw5$ make clean; make

# and run with
~/team-25/hw5$ ./main [inputFileName] [memSize(in GB)] [debugFlag(0/1/2/3)]

e.g. ./mySort file.txt 8 0 # for normal run
     ./mySort file.txt 8 3 # for debug run, branch 3
# code snippets of the class usages are included in the 

./mySort data/gs.out.1g 8 0 # load 1GB data, and sort with 8GB memory
./mySort data/gs.out.4g 8 0 
./mySort data/gs.out.16g 8 0 
./mySort data/gs.out.64g 8 0 

# The log files is located in ~/team-25/hw5/logs

# linux sort by ascii, run
LC_ALL=C sort data/gs.out.1g > gs.out.1g.linux.sorted