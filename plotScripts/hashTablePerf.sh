#!/usr/bin/env bash

function generateData() {
    echo "
10 9.000000 3.000000
50 41.000000 16.000000
100 54.000000 22.000000
500 255.000000 119.000000
1000 511.000000 240.000000
5000 2667.000000 1432.000000
10000 8654.000000 2729.000000
50000 12275.000000 8362.000000
100000 27236.000000 22556.000000
500000 182955.000000 168927.000000
" > /tmp/_
}

function doPlot() {
    echo "
set ytics font ',6'
set xtics font ',4'
set ylabel 'time (micro seconds)'
set xlabel 'numbers of key-value pairs'
plot '/tmp/_' u 1:2 t 'set k/v pairs' w l,\
'' u 1:3 t 'get k/v pairs' w l
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
