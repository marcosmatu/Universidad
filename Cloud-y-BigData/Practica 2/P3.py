from pyspark.sql import SparkSession
from pyspark.sql.functions import col, split, avg
import string

spark = SparkSession.builder.master('local').appName('PrecioMedio').getOrCreate()

df = spark.read.csv("GOOGLE.csv")

df.select(col("_c0").alias("fecha"), col("_c5").alias("coste")).withColumn("fecha",split(col("fecha"),'-').getItem(0)).groupBy("fecha").agg(avg(col("coste"))).sort("fecha",ascending = True).show()
