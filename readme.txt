# readme.txt for hw6

## Requirement
- gensort1.5
- Hadoop
- Spark
- Python3
- python/pandas
- python/matplotlib

## DIRECTORY STRUCTURE
.
├── mySort                      # source code and makefile for our mySort program, implemented in C++
│   ├── Makefile
│   ├── monitor                 # monitor scripts and logs for mySort and LinuxSort
│   │   ├── ...
│   │   ├── plot.py             # plotting scripts in python
│   │   └── monitor.sh
│   └── src
├── hadoop_src                  # source code for our hadoop sort program 
│   ├── ...
│   ├── hadoop_sort.sh          # scripts for Hadoop Sort
│   └── logs                    # logs for Hadoop Sort
├── spark_src                   # source code and makefile for our Spark Sort program,
|   ├── Makefile
|   ├── SparkSort.java
|   ├── SparkSort.sh            # scripts for Spark Sort
|   └── ...                     # logs for Spark Sort
└─── readme.txt

## Usage

### mySort & linuxSort
all experiments of mySort & linuxSort are wrapped in the mySort/monitor/monitor.sh

To run the experiments:
1. cd mySort/
2. make
3. monitor/monitor.sh [0 mySort | 1 Linux Sort] [dataset size in GB] [memory size for sorting in GB]


### hadoop sort
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

### spark sort
all experiments of Spark Sort are wrapped in the spark_src/SparkSort.sh

To run the experiments:
1. cd spark_src/
2. make 
3. SparkSort.sh [dataset size in GB]