#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: SparkSort.sh [dataset size in GB]"
    exit
fi

echo "Generating $1 GB dataset..."
gensort -a $((10000000*$1)) gs.out

echo "Importing $1 GB dataset to HDFS..."
$HADOOP_HOME/bin/hadoop fs -put gs.out /home/input/
rm gs.out

echo "Spark Sorting..."
$SPARK_HOME/bin/spark-submit --class SparkSort --master yarn --deploy-mode cluster --driver-memory 4g --executor-memory 2g --executor-cores 1 SparkSort.jar

echo "Exporting output from HDFS..."
$HADOOP_HOME/bin/hadoop fs -getmerge /home/output/data.out/ sort.out

echo "Formatiing and validating output file..."
unix2dos sort.out
valsort sort.out

echo "Cleaning dataset..."
$HADOOP_HOME/bin/hadoop fs -rm /home/input/gs.out
$HADOOP_HOME/bin/hadoop fs -rmr /home/output/data.out