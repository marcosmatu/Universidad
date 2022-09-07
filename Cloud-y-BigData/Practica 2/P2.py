from pyspark import SparkConf, SparkContext
import string

conf = SparkConf().setMaster('local').setAppName('contadorURL')
sc = SparkContext(conf = conf)

access_log_RDD = sc.textFile("access_log")

access_log_RDD.flatMap(lambda line: line.split()).filter(lambda word: word[0] == '/').map(lambda url: (url,1)).reduceByKey(lambda x,y: x+y).saveAsTextFile("output")
