#!/usr/bin/gnuplot
set terminal png size 1920,1080 enhanced font 'Arial, 16'
set output 'Results.png'

set style line 1 linecolor rgb 'red' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 0
#set format y "%.6f"
set xlabel "Символы" font "Arial, 16"
#set format x "%.0f"
set ylabel "Число совпадений" font "Arial, 16"
set xtics 128 font "Arial, 12"
set ytics 65000 font "Arial, 12"
#set ytics font "Arial, 12"
set rmargin 4
set tmargin 2
set mxtics

plot "results.dat" using 1:2 title "Распределение" with linespoints ls 1
