from pyspark import SparkConf, SparkContext
import string
import sys

conf = SparkConf().setMaster('local').setAppName('BuscaPalabras')
sc = SparkContext(conf = conf)

textRDD = sc.textFile('input.txt')

palabraClave = sys.argv[1]

lineasConPalabraClave = textRDD.filter(lambda line: palabraClave in line)

lineasConPalabraClave.saveAsTextFile("output")
