#!/usr/bin/python3

import sys
import re

for line in sys.stdin:
    words = line.split(',')
    anyo = words[0]
    anyo = anyo[0:4]
    if anyo != "Date":
        print(anyo + '\t' + words[4])

