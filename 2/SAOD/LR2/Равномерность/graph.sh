#!/usr/bin/gnuplot
set terminal png size 1920,1080 enhanced font 'Arial, 16'
set output 'Hashs.png'

set style line 1 linecolor rgb 'red' linetype 3 linewidth 0
set style line 2 linecolor rgb 'green' linetype 3 linewidth 0
set style line 3 linecolor rgb 'blue' linetype 3 linewidth 0
set style line 4 linecolor rgb 'yellow' linetype 3 linewidth 0
set style line 5 linecolor rgb 'brown' linetype 3 linewidth 0

set border linewidth 1
set key top left
set grid
set mytics 0
set format y "%.6f"
set xlabel "" font "Arial, 16"
set format x "%.0f"
set ylabel "Число коллизий" font "Arial, 16"
set xtics 127 font "Arial, 12"
set ytics font "Arial, 12"
set rmargin 4
set tmargin 2
set mxtics

plot "ADD_Hash.dat" using 1:2 title "ADD Hash" with linespoints ls 1,\
     "FNV_Hash.dat" using 1:2 title "FNV Hash" with linespoints ls 2,\
     "JENKINS_one_at_a_time_Hash.dat" using 1:2 title "JENKINS one at a time Hash" with linespoints ls 3,\
     "KP_Hash.dat" using 1:2 title "KP Hash" with linespoints ls 4,\
     "XOR_Hash.dat" using 1:2 title "XOR Hash" with linespoints ls 5
