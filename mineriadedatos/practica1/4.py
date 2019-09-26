# -*- coding: utf-8 -*-
"""Implemente un programa Python que lea una matriz de
número enteros
 desde teclado de una dimensión dada. A
partir de la matriz leída debe calcular la siguiente información:
4.1.
Moda de la matriz.
4.2.
Media de todos los elementos de la matriz."""

import numpy as np
from scipy import stats

print('Introduce el numero de filas')
filas = int(input())

print('Introduce el numero de columnas')
columnas = int(input())

print('Escribe la matriz por teclado')
m = np.zeros((filas, columnas))

for i in range(filas):
    for j in range(columnas):
        m[i][j]=int(raw_input())
print(m)

print('La media de los elementos de la matriz es :')
media=np.average(m)
print('Resultado: ',media)

print('La moda de los elementos de la matriz es :')
a=[]
for i in range(filas):
    for j in range(columnas):
        a.append(m[i][j])
moda=stats.mode(a)
print('Resultado: ', moda[0][0])

