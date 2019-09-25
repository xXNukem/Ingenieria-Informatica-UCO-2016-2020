#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafico.eps"
set key right bottom
set xlabel "Tamanyo del ejemplar"
set ylabel "Tiempo de ejecucion"
plot 'Datos.txt' using 1:2 t "Tiempo practico frente a tamanyo" w l, 'Datos.txt' using 1:3 t "Tiempo teorico frente a tamanyo" w l 
_end_
