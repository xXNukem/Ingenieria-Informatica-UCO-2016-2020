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
filas=int(input())
 
print('Introduce el numero de columnas')
columnas=int(input())
 
print('Generando matriz...')
 
m=np.zeros((filas, columnas))
a=np.arange(10,50)

for i in range(filas):
    for j in range(columnas):
        m[i][j]=np.random.choice(a)
        
        
print(m)

print('Obteniendo valores')

min=m[0][0]

for i in range(filas):
    for j in range(columnas):
        if m[i][j]<min:
            min=m[i][j]
            
print('El valor minimo de la matriz es: ',min)

max=m[0][0]

for i in range(filas):
    for j in range(columnas):
        if m[i][j]>max:
            max=m[i][j]

print('El valor maximo de la matriz es: ', max)

a=np.array

for i in range(2):
    print('Producto escalar, introduce la cordenada de los dos vectores:')
    print('Introduce f para vector de fila o c para vector de columna ')
    opc=input()

    if opc=="f":
        print('Introduce la fila de la que extraes el vector')
        fila=int(input())
        if fila <=filas and fila>=0:
            a[i]=m[fila,:]
    elif opc=="c":
        print('Introduce la columna de la que extraes el vector')
        col=int(input())
        if col <=columnas and col>=0:
            a[i]=m[:,col]
    else:
        print('Opcion invalida, por defecto se elige un vector columna' )
        col=int(input())
        if col <=columnas and col>=0:
            a[i]=m[:,col]


print(a)

