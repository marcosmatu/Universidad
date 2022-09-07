#!/usr/bin/python3

import sys
import csv
import re

reader = csv.reader(sys.stdin)

for line in reader:
    if line[3] != "recclass" and line[4] != '':
        print(line[3] + '\t' + line[4])

 

