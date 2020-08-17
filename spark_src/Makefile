SparkSort.jar: SparkSort.class
	jar cvf SparkSort.jar SparkSort.class
SparkSort.class: SparkSort.java
	javac -cp ${SPARK_HOME}/jars/spark-core_2.12-3.0.0-preview2.jar:${SPARK_HOME}/jars/scala-library-2.12.10.jar SparkSort.java

.PHONY: clean
clean:
	rm *jar *class
