#!/usr/bin/gnuplot
set title 'График зависимости ускорения от числа потоков'
set terminal png size 800,600 enhanced font 'Arial, 16'
set output 'graph.png'

set style line 1 linecolor rgb '#ff5500' linetype 1 linewidth 2
set style line 2 linecolor rgb '#ff00ff' linetype 1 linewidth 2
set style line 3 linecolor rgb '#666666' linetype 1 linewidth 2

set style line 4 linecolor rgb '#00ff00' linetype 1 linewidth 2
set style line 5 linecolor rgb '#ccffcc' linetype 1 linewidth 2
set style line 6 linecolor rgb '#1100ff' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 0
set format y "%.0f"
set xlabel "Потоки" font "Arial, 16"
set format x "%.3f"
set ylabel "Ускорение" font "Arial, 16"
set xtics 1 font "Arial, 12" format '%.0f'
set ytics 0.1 font "Arial, 12" format '%.1f'
set rmargin 4
set tmargin 2
set mxtics

plot "25000000.dat" using 1:2 title "25M" with linespoints ls 1,\
     "100000000.dat" using 1:2 title "100M" with linespoints ls 2,\
     "225000000.dat" using 1:2 title "225M" with linespoints ls 3,\
     "400000000.dat" using 1:2 title "400M" with linespoints ls 4,\
     "625000000.dat" using 1:2 title "625M" with linespoints ls 5,\
     "900000000.dat" using 1:2 title "900M" with linespoints ls 6
