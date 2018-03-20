#!/usr/bin/env bash

function generateData() {
    echo "
10 7.000000
50 21.000000
100 35.000000
500 149.000000
1000 298.000000
5000 1558.000000
10000 3373.000000
50000 23799.000000
100000 48514.000000
500000 285634.000000
" > /tmp/_
}

function doPlot() {
    echo "
set ytics font ',6'
set xtics font ',4'
set ylabel 'time (micro seconds)'
set xlabel 'numbers of key-value pairs'
plot '/tmp/_' u 1:2 t 'set k/v pairs' w l
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
