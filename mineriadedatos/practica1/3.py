# -*- coding: utf-8 -*-
""" Implemente un programa Python que lea una matriz de
número reales
 desde teclado de una dimensión dada. A
partir de la matriz leída debe calcular la siguiente información:
3.1.
Máximo por filas y por columnas
3.2.
Determinante de la matriz.
3.3.
(
*
) Rango de la matriz"""

import numpy as np

print('Introduce el numero de filas')
filas = int(input())

print('Introduce el numero de columnas')
columnas = int(input())

print('Escribe la matriz por teclado')
m = np.zeros((filas, columnas))

for i in range(filas):
    for j in range(columnas):
        m[i][j]=float(raw_input())
print(m)

print('Mostrando maximos de cada fila')

for i in range(filas):
    vector=m[i, :]
    max=np.max(vector)
    print('El maximo de la fila', i, 'es: ',max)

print('Mostrando minimos de cada fila')

for i in range(filas):
    vector=m[i,:]
    min=np.min(vector)
    print('El minimo de la fila',i,'es:',min)

print('Mostrando maximos de cada columna')

for i in range(columnas):
    vector=m[:, i]
    max=np.max(vector)
    print('El maximo de la columna', i, 'es: ',max)

print('Mostrando minimos de cada columna')

for i in range(columnas):
    vector=m[:,i]
    min=np.min(vector)
    print('El minimo de la columna',i,'es:',min)

if filas==columnas:
    print('Calculando determinante de la matriz')
    determinante = np.linalg.det(m)
    print('Resultado: ', determinante)
else:
    print('Para calcular el determinante el numero de filas y columnas deben ser iguales')
