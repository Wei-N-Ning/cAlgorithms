#!/usr/bin/env bash

function generateData() {
    echo "
9 7.000000
54 30.000000
324 247.000000
1944 1924.000000
11664 14687.000000
69984 107419.000000
419904 771824.000000
2519424 5686863.000000
" > /tmp/_
}

function doPlot() {
    echo "
set xtics font ',4'
set ytics font ',4'
plot '/tmp/_' u 1:2 t '' w lp pt 4 ps 2.0
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
