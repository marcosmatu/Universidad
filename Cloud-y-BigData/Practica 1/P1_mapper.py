#!/usr/bin/python3

import sys
import re

contLinea = 0

for line in sys.stdin:
    words = re.sub(r'\W+', ' ', line).split()
    contLinea += 1
    for word in words:
        if word == sys.argv[1]:
            print(word.lower() + "\t" , contLinea)
   

