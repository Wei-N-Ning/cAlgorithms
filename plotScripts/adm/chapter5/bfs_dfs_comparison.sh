#!/usr/bin/env bash

function generateData() {
    echo "
# NumElements Time
100 226.000000
500 1355.000000
1000 2983.000000
5000 24052.000000
10000 50520.000000
50000 391561.000000
100000 933843.000000
500000 6685657.000000
" > /tmp/bfs_

    echo "
# NumElements Time
100 128.000000
500 798.000000
1000 1708.000000
5000 13745.000000
10000 29082.000000
50000 244074.000000
100000 598736.000000
500000 3798683.000000
" > /tmp/dfs_
}

function doPlot() {
    echo "
set key outside top center
set xtics font ',4'
set ytics font ',4'
u=0
plot '/tmp/bfs_' u 1:2 t 'bfs' w l lw 2,\
'/tmp/dfs_' u 1:2 t 'dfs' w l lw 2
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
