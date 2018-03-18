#!/usr/bin/env bash

# Samples: 76  of event 'cycles'
# Event count (approx.): 32792291
#
# Overhead  Command          Shared Object      Symbol
# ........  ...............  .................  ......................
#
#    55.35%  cciBinaryTreePe  cciBinaryTreePerf  [.] _insert
#    23.17%  cciBinaryTreePe  cciBinaryTreePerf  [.] CompareI
#    10.00%  cciBinaryTreePe  cciBinaryTreePerf  [.] Traverse
#     5.74%  cciBinaryTreePe  cciBinaryTreePerf  [.] doInsert
#     2.87%  cciBinaryTreePe  cciBinaryTreePerf  [.] CreateBinTreeNode
#     1.44%  cciBinaryTreePe  [kernel]           [k] 0xffffffffbe9b84b7
#     1.44%  cciBinaryTreePe  cciBinaryTreePerf  [.] touchNode
#     0.00%  perf             [kernel]           [k] 0xffffffffbe867d36


function generateData() {
    echo "
10 2.000000 1.000000
100 12.000000 2.000000
200 23.000000 4.000000
500 72.000000 9.000000
1000 165.000000 21.000000
5000 1133.000000 94.000000
10000 2598.000000 222.000000
20000 6065.000000 519.000000
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

