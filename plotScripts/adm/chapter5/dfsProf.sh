#!/usr/bin/env bash

function generateData() {
    echo "
# NumElements Time
100 886.000000
500 3196.000000
1000 5432.000000
5000 45819.000000
10000 113316.000000
50000 1249084.000000
100000 3075397.000000
500000 26216422.000000
" > /tmp/_
}

function doPlot() {
    echo "
set key outside top center
set xtics font ',4'
set ytics font ',4'
u=0
plot '/tmp/_' u 1:2 t 'original' w l lw 2,\
'' u 1:(v=\$2-u, u=\$2, v) t 'differencing' w l lw 3
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
