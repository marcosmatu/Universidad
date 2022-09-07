from pyspark.sql import SparkSession
from pyspark.sql.functions import col, split, avg
import string

spark = SparkSession.builder.master('local').appName('AVGmasa').getOrCreate()

df = spark.read.csv("Meteorite_Landings.csv")

df.select(col("_c3").alias("Meteorito"), col("_c4").alias("Masa")).groupBy("Meteorito").agg(avg(col("Masa"))).sort("Meteorito", ascending = True).show(df.count())
