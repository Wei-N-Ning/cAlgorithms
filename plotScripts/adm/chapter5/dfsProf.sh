#!/usr/bin/env bash

function generateData() {
    echo "
# NumElements Time
100 148.000000
500 877.000000
1000 1821.000000
5000 15237.000000
10000 33938.000000
50000 267992.000000
100000 642566.000000
500000 4551116.000000
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
