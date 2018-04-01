#!/usr/bin/env bash

function generateData() {
    echo "
workload mergesort heapsort quicksort(Hr)
34 31.000000 15.000000 6.000000
204 212.000000 129.000000 42.000000
1224 1622.000000 1051.000000 366.000000
7344 12149.000000 8129.000000 2792.000000
44064 85596.000000 59560.000000 20640.000000
264384 604934.000000 430540.000000 149750.000000
1586304 4450756.000000 3300222.000000 980310.000000
" > /tmp/_
}

function doPlot() {
    echo "
set key outside top center
set xtics font ',4'
set xtics font ',4'
plot '/tmp/_' u 1:2 t 'mergesort()' w lp pt 7 ps 0.5,\
'' u 1:3 t 'heapsort()' w lp pt 7 ps 0.5,\
'' u 1:4 t 'quicksort (Hoarse)' w lp pt 7 ps 0.5
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
