import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD; import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext; import scala.Tuple2;
import java.util.Arrays;
public class SparkSort {
 	public static void main(String[] args) {
		SparkConf sparkConf = new SparkConf().setAppName("SparkSort");
		JavaSparkContext sparkContext = new JavaSparkContext(sparkConf);
		String in = "hdfs://192.168.122.147:9000/home/input/gs.out";
		String out = "hdfs://192.168.122.147:9000/home/output/data.out";
		JavaRDD<String> textFile = sparkContext.textFile(in);
		JavaPairRDD<String, Integer> sort = textFile
			.flatMap(s -> Arrays.asList(s).iterator()) 
			.mapToPair(word -> new Tuple2<>(word, 1))
			.sortByKey();
		sort.keys().coalesce(1).saveAsTextFile(out);
	}
}
