#!/usr/bin/gnuplot
set terminal png size 1920,1080 enhanced font 'Arial, 16'
set output 'Graph2.png'

set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 2 linecolor rgb 'green' linetype 1 linewidth 2
set style line 3 linecolor rgb 'blue' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 0
set format y "%.6f"
set xlabel "Number of elements" font "Arial, 16"
set format x "%.0f"
set ylabel "Execution time (sec)" font "Arial, 16"
set xtics 1000000 font "Arial, 12"
set ytics font "Arial, 12"
set rmargin 4
set tmargin 2
set mxtics

plot "Bubble Sort.dat" using 1:2 title "Bubble sort" with linespoints ls 1,\
     "Odd-Even Sort.dat" using 1:2 title "Odd-Even sort" with linespoints ls 2,\
     "Insertion Sort.dat" using 1:2 title "Insertion sort" with linespoints ls 3
