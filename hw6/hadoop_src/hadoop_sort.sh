#!/bin/bash
# Execute this script from the hw6 directory so relative paths works well.
# ~/.../team-25/hw6 $./hadoop_src/hadoop_sort.sh
################################
# hadoop_sort.sh
# run this script to sort a local file using hadoop
# ##############################
# Preparations:
# 1. Make sure HDFS and YARN are running
# sbin/start-dfs.sh
# sbin/start-yarn.sh
# 2. Update the PRJ_DIR.
################################
SIZE_G=$1
# Paths to dirs and jars
PRJ_DIR=/exports/projects
HADOOP_PATH=$PRJ_DIR/hadoop-3.2.1
HADOOP_CLASSPATH=$($HADOOP_PATH/bin/hadoop classpath)
MAPRED_EXAMPLES_JAR=$PRJ_DIR/hadoop_jar/hadoop-mapreduce-examples-3.2.0.jar

# clean up all dirs
# local
rm -rf ./data
# on hadoop
$HADOOP_PATH/bin/hadoop fs -rm -r /home/output/gensort/*

# set up dirs
mkdir ./data
mkdir ./logs
# on hadoop
$HADOOP_PATH/bin/hadoop fs -mkdir /home/input
$HADOOP_PATH/bin/hadoop fs -mkdir /home/input/gensort
$HADOOP_PATH/bin/hadoop fs -mkdir /home/output
$HADOOP_PATH/bin/hadoop fs -mkdir /home/output/gensort

###############################
# Use teragen for data !DOES NOT WORK WITH VALSORT!
# $HADOOP_PATH/bin/hadoop fs -rm -r /home/input/tera/*
# workload size, num of records (100bytes per record)
# SIZE=10
# NAME=1k
#SIZE=$((1000000*1)) # 1g
#NAME=1g
# Use teragen to create workload files on hdfs
# $HADOOP_PATH/bin/hadoop jar $MAPRED_EXAMPLES_JAR teragen $SIZE /home/input/tera/$NAME.gen

# use gensort for workload data
SIZE=$((10000000*$SIZE_G)) # 
NAME=$SIZE_G.g
$PRJ_DIR/gensort-1.5/gensort -a $SIZE ./data/$NAME.gen
# put on hdfs
$HADOOP_PATH/bin/hadoop fs -put ./data/$NAME.gen /home/input/gensort/$NAME.gen

# remove the data from local
rm -rf ./data/*

##############################
# Recompile the Sort.jar
javac -Xdiags:verbose -classpath ${HADOOP_CLASSPATH} -d ./hadoop_src/Sort/ ./hadoop_src/Sort/Sort.java
jar -cvf ./Sort.jar -C ./hadoop_src/Sort/ .

# kill a specific job with
# bin/mapred job -list
# bin/mapred job -kill [jobid]

# run hadoop sort on gensort data
mkdir ~/team-25/hw6/hadoop_src/logs
{ time $HADOOP_PATH/bin/hadoop jar ./Sort.jar Sort /home/input/gensort/$NAME.gen /home/output/gensort/$NAME.sorted ; } 2>./hadoop_src/logs/$NAME.time.txt

# fetch the output from hdfs
# $HADOOP_PATH/bin/hadoop fs -mergeget /home/output/gensort/$NAME.sorted ./data
# validate with valsort, by hand
# { $PRJ_DIR/gensort-1.5/valsort ./data/$NAME.sorted/part-r-00000 ; } 2> ./hadoop_src/logs/$NAME.valsort.txt

# cleanup everything
rm -rf ./data
$HADOOP_PATH/bin/hadoop fs -rm -r /home/input/gensort/*
$HADOOP_PATH/bin/hadoop fs -rm -r /home/output/gensort/*

