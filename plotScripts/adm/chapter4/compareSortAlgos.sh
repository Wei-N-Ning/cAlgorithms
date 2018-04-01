#!/usr/bin/env bash

function generateData() {
    echo "
workload mergesort heapsort
34 32.000000 15.000000
204 215.000000 129.000000
1224 1643.000000 1060.000000
7344 12360.000000 8203.000000
44064 88566.000000 60557.000000
264384 612922.000000 440749.000000
1586304 4490106.000000 3342687.000000
" > /tmp/_
}

function doPlot() {
    echo "
set key outside top center
set xtics font ',4'
set xtics font ',4'
plot '/tmp/_' u 1:2 t 'mergesort()' w lp pt 7 ps 0.5,\
'' u 1:3 t 'heapsort()' w lp pt 7 ps 0.5
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
