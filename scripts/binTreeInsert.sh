#!/usr/bin/env bash

function generateData() {
    echo "
10 2.000000 1.000000
100 12.000000 1.000000
200 24.000000 3.000000
500 72.000000 7.000000
1000 167.000000 15.000000
5000 1163.000000 80.000000
10000 2682.000000 198.000000
20000 6155.000000 432.000000
" > /tmp/_
}

function doPlot() {
    echo "
set ytics font ',6'
set xtics font ',6'
set ylabel 'time (micro seconds)'
set xlabel 'numbers of ints inserted'
plot '/tmp/_' u 1:2 t 'binary tree insert()' w l,\
'' u 1:3 t 'binary tree traverse()' w l
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot

