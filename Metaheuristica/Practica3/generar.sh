#!/bin/bash
reset
cd build
cmake ../
make clean
make
cd ..
if [[ -d "Results" ]]; then
	rm Results/*
else
	mkdir Results
fi
./build/practica3 jeu_100_25_4.txt 3 > Results/100_25_4_3M.txt 
./build/practica3 jeu_100_25_4.txt 5 > Results/100_25_4_5M.txt 
./build/practica3 jeu_100_75_2.txt 3 > Results/100_75_2_3M.txt 
./build/practica3 jeu_100_75_2.txt 5 > Results/100_75_2_5M.txt 
./build/practica3 jeu_200_25_8.txt 3 > Results/200_25_8_3M.txt 
./build/practica3 jeu_200_25_8.txt 5 > Results/200_25_8_5M.txt 
./build/practica3 jeu_200_75_5.txt 3 > Results/200_75_5_3M.txt 
./build/practica3 jeu_200_75_5.txt 5 > Results/200_75_5_5M.txt 

./gnuplot.sh Results/100_25_4_3M.txt

./gnuplot.sh Results/100_25_4_5M.txt 

./gnuplot.sh Results/100_75_2_3M.txt 

./gnuplot.sh Results/100_75_2_5M.txt

./gnuplot.sh Results/200_25_8_3M.txt

./gnuplot.sh Results/200_25_8_5M.txt 

./gnuplot.sh Results/200_75_5_3M.txt

./gnuplot.sh Results/200_75_5_5M.txt 

if [[ -d "Graphics" ]]; then
	rm Graphics/*
else
	mkdir Graphics
fi
cp Results/*.eps Graphics
rm Results/*.eps