#!/usr/bin/python3

import sys

previous = None
sum = 0

for line in sys.stdin:
    key, value = line.split('\t')
    print("Rango " + key + ": " + value)
