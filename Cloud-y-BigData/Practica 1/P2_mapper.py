#!/usr/bin/python3

import sys
import re

for line in sys.stdin:

    indice_get = line.index('"')
    cadena = line[indice_get+1:len(line)]
    indice_comillas = cadena.index('"')
    cadena = cadena[:indice_comillas]
    print(cadena + "\t1")
