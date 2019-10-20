cat << end | gnuplot
set terminal postscript eps color
set output "$1.eps"
set key right bottom
set xlabel "Iteraciones"
set ylabel "CCR"
plot "$1" using 1 t "CCR TRAIN" w l lt rgb "red","$1" using 2 t "CCR TEST" w l lt rgb "blue","$1" using 3 t "VALIDATION ERROR" w l lt rgb "orange"
end
