# -*- coding: utf-8 -*-
"""Implemente un programa Python que lea una matriz de
número reales
 desde un fichero texto con formato libre.
Una vez leído el programa debe obtener la inversa de la matriz y realizar un producto matricial para comprobar
que el cálculo de la inversa es correcto"""

import numpy as np

m=np.loadtxt("fichero.txt", delimiter=' ')

print('Matriz leida del fichero: ')
print(m)

inv=np.linalg.inv(m)

print('Matriz inversa ')

print(inv)

print('Producto matricial')

prod=np.matmul(m,inv)
print(prod)

identidad=np.identity(np.size(m,1))
if np.array_equal(identidad,prod)==True:
    print('Es correcto')
else:
    print('No es correcto')

