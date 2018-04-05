#!/usr/bin/env bash

function generateData() {
    echo "
# NumElements Time
10 12.000000
20 25.000000
50 57.000000
100 129.000000
500 630.000000
1000 1629.000000
2000 3672.000000
" > /tmp/_
}

function doPlot() {
    echo "
plot '/tmp/_' u 1:2 t '' w l
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
