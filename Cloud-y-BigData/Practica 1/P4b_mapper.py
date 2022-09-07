#!/usr/bin/python3

import sys
import re
import math

for line in sys.stdin:
    key, value = line.split('\t')
    print(math.ceil(float(value)) , '\t' , key)
