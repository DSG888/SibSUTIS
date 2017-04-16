#!/usr/bin/gnuplot
set title 'График зависимости ускорения от числа потоков'
set terminal png size 1200,900 enhanced font 'Arial, 16'
set output 'graph.png'

set style line 1 linecolor rgb '#000000' linetype 1 linewidth 2
set style line 2 linecolor rgb '#ff0000' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set format y "%.0f"
set xlabel "Потоки\nn = " font "Arial, 16"
set format x "%.3f"
set ylabel "Ускорение" font "Arial, 16"
set xtics 1 font "Arial, 12" format '%.0f'
set ytics 0.5 font "Arial, 12" format '%.1f'
set rmargin 4
set tmargin 2
set mxtics

plot "line.dat" using 1:2 title "Лин.уск." with linespoints ls 1,\
     "v2.dat" using 1:2 title "Цик. расп." with linespoints ls 2
