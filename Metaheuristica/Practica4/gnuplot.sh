cat << end | gnuplot
set terminal postscript eps color
set output "$1Mochilas_GeneticAlgorithm_Current_Best.eps"
set key right bottom
set xlabel "Iteraciones"
set ylabel "Fitness"
plot [:45000] "$1" using 1 t "Actual Genetico" with points pointtype 5 pointsize 0.2 lt rgb "blue","$1" using 2 t "Mejor Genetico" w l lt rgb "red"

set terminal postscript eps color
set output "$1Mochilas_GeneticAlgorithm_BestPerIt_MediasPopulation_Off.eps"
set key right bottom
set xlabel "Iteraciones"
set ylabel "Fitness"
plot [:1000]"$1" using 3 t "Mejor Genetico por iteraciones" w l lt rgb "green", "$1" using 4 t "Media poblacion por iteraciones Genetico" w l dt 2 lt rgb "blue","$1" using 5 t "Media descendientes por iteraciones Genetico" w l dt 2 lt rgb "red"

set terminal postscript eps color
set output "$1Mochilas_ACO_Current_Best.eps"
set key right bottom
set xlabel "Iteraciones"
set ylabel "Fitness"
plot [:1100] "$1" using 6 t "Actual ACO" with points pointtype 5 pointsize 0.2 lt rgb "blue","$1" using 7 t "Mejor ACO" w l lt rgb "red"

set terminal postscript eps color
set output "$1Mochilas_ACO_Mean_AcoPerIt.eps"
set key right bottom
set xlabel "Iteraciones"
set ylabel "Fitness"
plot [:250] "$1" using 8 t "Mejor ACO por iteraciones" w l lt rgb "green", "$1" using 9 t "Media ACO por hormiga" w l dt 2 lt rgb "blue"
end
