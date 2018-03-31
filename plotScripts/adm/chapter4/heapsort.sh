#!/usr/bin/env bash

function generateData() {
    echo "
workload create-by-insert() create-by-heapify()
9 2.000000 1.000000
54 7.000000 5.000000
324 42.000000 30.000000
1944 260.000000 172.000000
11664 2203.000000 1055.000000
69984 9632.000000 6254.000000
419904 58080.000000 39715.000000
2519424 357387.000000 248192.000000
" > /tmp/_
}

function doPlot() {
    echo "
set key outside top center
set xtics font ',4'
set ytics font ',4'
plot '/tmp/_' u 1:2 t 'create-by-insert()' w lp pt 4 ps 2.0,\
'' u 1:3 t 'create-by-heapify()' w lp pt 4 ps 2.0
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
