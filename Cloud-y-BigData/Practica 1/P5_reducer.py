#!/usr/bin/python3

import sys

previous = None
sum = 0
dic = {}
dicAVG = {}

for line in sys.stdin:
    key, value = line.split('\t')
    if key in dic:
        dic[key] = dic[key] + float(value)
        dicAVG[key] = dicAVG[key] + 1
    else:
        dic[key] = float(value)
        dicAVG[key] = 1

for clave in dic:
    print(clave + '\t', dic[clave]/dicAVG[clave])
