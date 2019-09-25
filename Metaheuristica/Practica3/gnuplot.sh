cat << end | gnuplot
set terminal postscript eps color
set output "$1Mochilas_Enfriamiento_Simulado.eps"
set key right bottom
set xlabel "Iteraciones"
set ylabel "Fitness"
plot "$1" using 1 t "currentSA" w l dt 2 lt rgb "red","$1" using 2 t "bestSA" w l lt rgb "orange"


set terminal postscript eps color
set output "$1Mochilas_Tabu_Grasp_Iterative.eps"
set key right bottom
set xlabel "Iteraciones"
set ylabel "Fitness"
plot [:1700] "$1" using 3 t "currentTS" w l dt 2 lt rgb "red","$1" using 4 t "bestTS" w l lt rgb "#B40431","$1" using 5 t "currentGrasp" w l dt 2 lt rgb "blue","$1" using 6 t "bestGrasp" w l lt rgb "#0000FF","$1" using 7 t "currentIG" w l dt 2 lt rgb "green","$1" using 8 t "bestIG" w l lt rgb "#298A08"

end
