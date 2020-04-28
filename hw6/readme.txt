TODO: write me
# readme.txt for hw6

# DIRECTORY STRUCTURE
# There are 3 subdirectories in the hw6 directory: hadoop_src, mySort, and spark_src
# - hadoop_src contains the source code for our hadoop sort program
# - mySort contains the source code and makefile for our internal & external sort program, implemented in C++
# - spark_src !.......!


# RERUNING THE EXPERIMENTS
# 

# mySort


# linux-sort


# hadoop sort
# preparations
# create a project directory and set the PRJ_DIR to it
# Make sure gensort binary is downloaded into that directory
# and HADOOP_PATH to your hadoop installation
# To run the hadoop sort experiments, navigate to the hw6 directory, and run
~/.../team-25/hw6 $./hadoop_src/hadoop_sort.sh [expsize]
# where [expsize] specifies the workload size created by gensort, in GBs.
# it recompiles the hadoop sort program from source, and submits the job to yarn.
# The log files from for the experiment will be saved in the ./hw6/hadoop_src/logs, which includes the timed results of the experiment
ls ./hadoop_src/logs

# spark