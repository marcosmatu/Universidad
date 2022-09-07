from pyspark.sql import SparkSession
from pyspark.sql.functions import col, split, avg, ceil
import string

spark = SparkSession.builder.master('local').appName('Valoracion').getOrCreate()

df = spark.read.csv("ratings.csv")

df.select(col("_c1").alias("idPelicula"),col("_c2").alias("valoracion")).groupBy("idPelicula").agg(avg(col("valoracion"))).select(ceil(col("avg(valoracion)")).alias("rangoValoracion"), col("idPelicula")).sort("rangoValoracion", ascending=True).rdd.map(lambda x: ("Range " + str(x["rangoValoracion"]), x["idPelicula"])).saveAsTextFile("output")
