TODO: writeme

# To run the all the experiments, clone the repo and navigate to the hw3 directory
~/.../ $ git clone https://gitlab.com/cs553-spring2020/team-25.git


# compilation commands
# in the hw3 directory, run
~/.../team-25/hw3 $ make clean; make

# change permission for scripts
~/.../team-25/hw3 $ chmod -R 777 src/scripts

# and run the program with
~/.../team-25/hw3 $ ./main

# which would create the result files in the same directory as the program.
# name of the result files:
# for RR, RS:
# 64k_1m_16m-RS_result.txt
# 64k_1m_16m-RR_result.txt
# 4k-iops_result.txt
# which are all csv files.

# for WR, WS:
# the program will start the writing benchmark first and there's no need to create an empty file for the benchmark
# the program will automatically generate a new file
# it will start from testing the IOPS of 4KB record then start to do the testing of throughput in different record size and thread count
# it will do the random access first then do sequential access
# the result will be printed out on the screen
# to catch the output as a file, please use command line tool such like 
~/.../team-25/hw3 $ ./main > output.txt


#########  IOZONE  #########
#
### Iozone_test.sh ###
#
#To test our Iozone code, run our userfriendly Iozone_test.sh bashscript
#You will have to specify the pattern and the number of threads.
#The pattern you want to run between :
#   "RS" to run the sequential read/write
#   "RR" to run the random read/write operation
#   "OPS" to run the random read/write operation and get the result in OPS/s 
#The number of threads you want between 1 2 4 8 12 24 48
#After pressing the "enter" key, you will get the result for the 3 records types of your configuration
#
### IOPS.sh ###
#
#Run this bash script to have the results of all the different configurations in OPS/s
#
### throughput.sh ###
#
#Run this bash script to get the results of all the different configurations in KB/s
#
##
