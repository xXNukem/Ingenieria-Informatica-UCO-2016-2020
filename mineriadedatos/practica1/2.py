# -*- coding: utf-8 -*-
"""Implemente un programa Python que genere aleatoriamente una matriz de valores reales de un tamaño indicado 
por teclado. Sobre la matriz generada realice las siguientes operaciones:
2.1.
Obtenga los valores máximos y mínimos de la matriz.
2.2.
Use el producto escalar para obtener el ángulo formado por dos vectores fila o columna solicitados por 
teclado."""

import numpy as np

print('Introduce el numero de filas')
filas = int(input())

print('Introduce el numero de columnas')
columnas = int(input())

print('Generando matriz...')

m = np.zeros((filas, columnas))
a = np.arange(10, 50)

for i in range(filas):
    for j in range(columnas):
        m[i][j] = np.random.choice(a)

print(m)

print('Obteniendo valores')

min = m[0][0]

for i in range(filas):
    for j in range(columnas):
        if m[i][j] < min:
            min = m[i][j]

print('El valor minimo de la matriz es: ', min)

max = m[0][0]

for i in range(filas):
    for j in range(columnas):
        if m[i][j] > max:
            max = m[i][j]

print('El valor maximo de la matriz es: ', max)

a = []

for i in range(2):
    print('Producto escalar, introduce la cordenada de los dos vectores:')
    print('Introduce f para vector de fila o c para vector de columna ')
    opc = input()

    if opc == "f":
        print('Introduce la fila de la que extraes el vector')
        fila = int(input())
        if filas >= fila >= 0:
            a.append(m[fila, :])
    elif opc == "c":
        print('Introduce la columna de la que extraes el vector')
        col = int(input())
        if columnas >= col >= 0:
            a.append(m[:, col])
    else:
        print('Opcion invalida, por defecto se elige un vector columna')
        col = int(input())
        if columnas >= col >= 0:
            a.appendm(m[:, col])

print('Obteniendo el angulo de los vectores seleccionados')
map(int, a)
escalar = np.dot(a[0], a[1])
norma1=np.linalg.norm(a[0])
norma2=np.linalg.norm(a[1])
angulo=escalar/(norma1*norma2)

print('Coseno del angulo: ', angulo)

