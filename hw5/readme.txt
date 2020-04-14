TODO: write me

##########################
# To run all mySort experiments, use the script:
~/team-25/hw5$ screen -S mySortTest ./run_exp.sh
# The log files are located in ~/team-25/hw5/logs
##########################
* Reminder: detach with ctrl+A+D, Reattach with screen -r mySortTest

##########################
# RUNNING TESTS MANUALLY # 
# To create data files with gensort, first download the binary from http://www.ordinal.com/gensort.html
# and run the script with
~/team-25/hw5$ ./src/scripts/createData.sh

# compile with
~/team-25/hw5$ make clean; make

# and run with
~/team-25/hw5$ ./main [inputFileName] [memSize(in GB)] [debugFlag]
# Debug flag options
# 0 - normal run
# 1 to 9: debug runs, with class usage examples. See source for details. 

e.g. ./mySort file.txt 8 0 # for normal run, and sort file.txt with 8GB of memory
     ./mySort file.txt 8 3 # for debug run, branch 3

# Run with gensort data
./mySort data/gs.out.1g 8 0 # load 1GB data, and sort with 8GB memory
./mySort data/gs.out.4g 8 0 
./mySort data/gs.out.16g 8 0 
./mySort data/gs.out.64g 8 0 
#########################


# linux sort by ascii, run
LC_ALL=C sort -S 8G data/gs.out.1g > linux_sorted/gs.out.1g.linux.sorted
LC_ALL=C sort -S 8G data/gs.out.4g > linux_sorted/gs.out.4g.linux.sorted
LC_ALL=C sort -S 8G data/gs.out.16g > linux_sorted/gs.out.16g.linux.sorted
LC_ALL=C sort -S 8G data/gs.out.64g > linux_sorted/gs.out.64g.linux.sorted

# check difference
diff data/gs.out.1g linux_sorted/gs.out.1g.linux.sorted # output should be blank
# etc...


