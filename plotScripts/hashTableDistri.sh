#!/usr/bin/env bash

function generateData() {
    echo "
10 0.600000 0.300000 0.300000
50 0.680000 0.060000 0.300000
100 0.650000 0.040000 0.270000
500 0.634000 0.010000 0.272000
1000 0.640000 0.005000 0.264000
5000 0.635400 0.001200 0.265600
10000 0.631400 0.000700 0.262300
50000 0.630580 0.000140 0.267240
100000 0.631860 0.000080 0.264150
500000 0.632438 0.000016 0.264314
" > /tmp/_
}

function doPlot() {
    echo "
set key outside top center
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set boxwidth 1
set xtic font ',5'
set ytic font ',5'
unset xtics
plot [][0:1.0] '/tmp/_' u 2 t 'utilization (longer the better)' lt rgb '#33FF66',\
'' u 3 t 'chain factor (longest chain / total size)' lt rgb '#FF9933',\
'' u 4 t 'collision rate (shorter the better)' lt rgb '#FF3333',\
'' u 0:(\$2):1 t '' with labels font ',3' offset -0.75,0.25
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot