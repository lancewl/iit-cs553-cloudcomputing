import java.io.IOException;
import java.util.StringTokenizer;
import java.nio.charset.Charset;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.*;

import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class Sort {

  public static class LineNullMapper
       extends Mapper<Object, Text, Text, NullWritable>{
    private final static NullWritable empty = NullWritable.get();
    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
     // using gensort data 
     byte[] bytArray = value.getBytes(); // 99 bytes.
     byte[] eol = "\n".getBytes();
     byte[] result = new byte[bytArray.length+eol.length];
     System.arraycopy(bytArray, 0, result, 0, bytArray.length);
     System.arraycopy(eol, 0, result, bytArray.length, eol.length);      
     Text line = new Text(result);
     context.write(line, empty);
     
     /*
     // using teragen data
      byte[] bytArray = value.getBytes();
      long numRecords = bytArray.length/100;
      for(int i=0; i<numRecords; i++){
        byte[] k = new byte[10];
	byte[] rowid = new byte[10];
	byte[] filler = new byte[78];
	byte[] result = new byte[10+10+79];

	System.arraycopy(bytArray, i*100, k, 0, 10);
	System.arraycopy(bytArray, i*100+10, rowid, 0, 10);
	System.arraycopy(bytArray, i*100+20, filler, 0, 78);

	// fill it to result
	System.arraycopy(k, 0, result, 0, k.length);
        System.arraycopy(rowid, 0, result, 10, rowid.length);
	System.arraycopy(filler, 0, result, 20, filler.length);	
	Text line = new Text(result);
	context.write(line, empty);
      }
      */

    }
  }

  public static class SortReducer
       extends Reducer<Text,NullWritable,Text,NullWritable> {
    private final static NullWritable empty = NullWritable.get();
    public void reduce(Text key, Iterable<NullWritable> values,
                       Context context
                       ) throws IOException, InterruptedException {
      for(NullWritable value: values){
	
        context.write(key, empty);
      }
    }
  }

  public static class MyKeyComparator extends WritableComparator{
    protected MyKeyComparator(){
      super(Text.class, true);
    }

    @Override
    public int compare(WritableComparable key1, WritableComparable key2){
      Text k1 = (Text) key1;
      Text k2 = (Text) key2;
      byte[] ba1 = k1.getBytes();
      byte[] ba2 = k2.getBytes();
      // should have same length
      for(int i=0; i<ba1.length; i++){
	int diff = Byte.compare(ba1[i],ba2[i]);
	if(diff!=0){
	  return diff;
	}
      }
      return 0;
    }

  }



  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "sort");
    job.setJarByClass(Sort.class);
    job.setMapperClass(LineNullMapper.class);
    job.setCombinerClass(SortReducer.class);
    job.setReducerClass(SortReducer.class);
    // set sort comparator
    job.setSortComparatorClass(MyKeyComparator.class);

    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(NullWritable.class);
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
