# -*- coding: utf-8 -*-
"""Implemente un programa Python que lea una matriz de
número reales
 desde un fichero texto con formato libre.
Una vez leído el programa debe obtener la inversa de la matriz y realizar un producto matricial para comprobar
que el cálculo de la inversa es correcto"""

import numpy as np

fichero=open('fichero.txt')
fichero.read()

x = []
for line in fichero.readlines():
    y = [v for v in line.split()]
    if y != []:
        x.append(int(y[0]));

print (x)