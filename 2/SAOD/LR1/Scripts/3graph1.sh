#!/usr/bin/gnuplot
set terminal png size 1920,1080 enhanced font 'Arial, 16'
set output 'Graph1.png'

set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 2 linecolor rgb 'green' linetype 1 linewidth 2
set style line 3 linecolor rgb 'blue' linetype 1 linewidth 2
set style line 4 linecolor rgb '#00ffee' linetype 1 linewidth 2
set style line 5 linecolor rgb '#ff5500' linetype 1 linewidth 2

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

plot "Counting Sort.dat" using 1:2 title "Counting sort" with linespoints ls 1,\
     "Quick Sort.dat" using 1:2 title "Quick sort" with linespoints ls 2,\
     "Radix Sort.dat" using 1:2 title "Radix Sort" with linespoints ls 3,\
     "Merge Sort.dat" using 1:2 title "Merge sort" with linespoints ls 4,\
     "Heap Sort.dat" using 1:2 title "Heap sort" with linespoints ls 5,\
