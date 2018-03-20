#!/usr/bin/env bash

# Samples: 57  of event 'cycles'
# Event count (approx.): 41579270
#
# Overhead  Command          Shared Object     Symbol
# ........  ...............  ................  ......................
#
#    46.21%  cciArrayListPer  cciArrayListPerf  [.] AlEmplaceBack
#    14.14%  cciArrayListPer  cciArrayListPerf  [.] appendToArrayList
#    13.68%  cciArrayListPer  cciArrayListPerf  [.] appendToCArray
#     4.96%  cciArrayListPer  [kernel]          [k] 0xffffffffbf0d7ac0
#     3.64%  cciArrayListPer  [kernel]          [k] 0xffffffffbec57297
#     2.02%  cciArrayListPer  [kernel]          [k] 0xffffffffbe9e7d0e
#     2.02%  cciArrayListPer  [kernel]          [k] 0xffffffffbf0d6540
#     2.02%  cciArrayListPer  [kernel]          [k] 0xffffffffbea35e96
#     2.02%  cciArrayListPer  [kernel]          [k] 0xffffffffbe9b84c9
#     2.00%  cciArrayListPer  [kernel]          [k] 0xffffffffbe9ba13e
#     1.99%  cciArrayListPer  [kernel]          [k] 0xffffffffbe9b7ab7
#     1.99%  cciArrayListPer  [kernel]          [k] 0xffffffffbe9c2b0a
#     1.99%  cciArrayListPer  [kernel]          [k] 0xffffffffbe9b77a2
#     1.31%  cciArrayListPer  [kernel]          [k] 0xffffffffbe9f77c6
#     0.00%  perf             [kernel]          [k] 0xffffffffbe867d36
#

function generateData() {
    echo "
100 1.000000 5.000000
500 1.000000 6.000000
1000 2.000000 8.000000
10000 17.000000 90.000000
50000 96.000000 367.000000
100000 179.000000 765.000000
500000 1058.000000 3449.000000
1000000 1999.000000 6764.000000
" > /tmp/_
}

function doPlot() {
    echo "
set ytics font ',6'
set xtics font ',4'
set ylabel 'time (micro seconds)'
set xlabel 'total number of ints'
plot '/tmp/_' u 1:2 t 'append to c-array' w l,\
'' u 1:3 t 'append to array list' w l
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
