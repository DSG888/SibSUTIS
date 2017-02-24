#!/usr/bin/gnuplot
set title 'Заполнение'
set terminal png size 800,600 enhanced font 'Arial, 16'
set output 'FillingGraph.png'

set style line 1 linecolor rgb 'blue' linetype 4 pi -1 linewidth 3
set style line 2 linecolor rgb 'red' linetype 4 pi -1 linewidth 3
set style line 3 linecolor rgb 'green' linetype 4 pi -1 linewidth 3

set style line 4 linecolor rgb 'blue' linetype 2 linewidth 2
set style line 5 linecolor rgb 'red' linetype 2 linewidth 2
set style line 6 linecolor rgb 'green' linetype 2 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 0
set format y "%.0f"
set xlabel "Число элементов" font "Arial, 16"
set format x "%.0f"
set ylabel "Время выполнения (секунды)" font "Arial, 16"
set xtics 10000000 font "Arial, 12" format '%.0s%c'
set ytics font "Arial, 12"
set rmargin 4
set tmargin 2
set mxtics

plot "FillingBSTreeRand.dat" using 1:2 title "BSTree Rand" with linespoints ls 1,\
     "FillingRBTreeRand.dat" using 1:2 title "RBTree Rand" with linespoints ls 2,\
     "FillingAATreeRand.dat" using 1:2 title "AATree Rand" with linespoints ls 3,\
     "FillingBSTreeSort.dat" using 1:2 title "BSTree Sort" with linespoints ls 4,\
     "FillingRBTreeSort.dat" using 1:2 title "RBTree Sort" with linespoints ls 5,\
     "FillingAATreeSort.dat" using 1:2 title "AATree Sort" with linespoints ls 6
