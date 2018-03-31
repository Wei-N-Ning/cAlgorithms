#!/usr/bin/env bash

# chapter 4, 4.6

function generateData() {
    echo "
10 6948.000000
100 65361.000000
1000 496010.000000
5000 2455285.000000
10000 4925853.000000
20000 9839062.000000
" > /tmp/_
}

function doPlot() {
    echo "
set xtics font ',5'
plot '/tmp/_' u 1:2 t '' w lp ps 2 pt 6
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
