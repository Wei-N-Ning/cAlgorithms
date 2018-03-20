#!/usr/bin/env bash

#Samples: 5K of event 'cycles', Event count (approx.): 4542662266
#Overhead  Command       Shared Object     Symbol
#  11.67%  cciQueuePerf  libc-2.23.so      [.] _int_malloc
#   7.57%  cciQueuePerf  cciQueuePerf      [.] newInt
#   7.18%  cciQueuePerf  cciQueuePerf      [.] invalid
#   6.96%  cciQueuePerf  cciQueuePerf      [.] Get
#   6.28%  cciQueuePerf  cciQueuePerf      [.] validateIndex
#   6.10%  cciQueuePerf  libc-2.23.so      [.] _int_free
#   5.88%  cciQueuePerf  cciQueuePerf      [.] CCIQueueFront
#   4.95%  cciQueuePerf  cciQueuePerf      [.] Remove
#   4.41%  cciQueuePerf  libc-2.23.so      [.] malloc
#   4.10%  cciQueuePerf  cciQueuePerf      [.] node
#   3.97%  cciQueuePerf  cciQueuePerf      [.] deleteNode
#   3.83%  cciQueuePerf  cciQueuePerf      [.] createNode
#   3.72%  cciQueuePerf  cciQueuePerf      [.] Dequeue
#   3.29%  cciQueuePerf  cciQueuePerf      [.] insert
#   3.06%  cciQueuePerf  cciQueuePerf      [.] Enqueue
#   2.76%  cciQueuePerf  libc-2.23.so      [.] free
#   2.35%  cciQueuePerf  cciQueuePerf      [.] Append
#   2.12%  cciQueuePerf  cciQueuePerf      [.] doEnqueue
#   1.66%  cciQueuePerf  cciQueuePerf      [.] doDequeue
#   1.49%  cciQueuePerf  [kernel]          [k] 0xffffffff9f0d7ac0
#   1.21%  cciQueuePerf  [kernel]          [k] 0xffffffff9ec57297
#   0.76%  cciQueuePerf  [kernel]          [k] 0xffffffff9f0d6540
#   0.28%  cciQueuePerf  cciQueuePerf      [.] free@plt
#   0.15%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9b7ced
#   0.13%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9b84b7
#   0.11%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9e7d0e
#   0.09%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9c2b0a
#   0.09%  cciQueuePerf  libc-2.23.so      [.] sysmalloc
#   0.07%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9e9d10
#   0.07%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9c20f1
#   0.07%  cciQueuePerf  [kernel]          [k] 0xffffffff9ea00026
#   0.06%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9d51ea
#   0.06%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9c38e1
#   0.06%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9bb247
#   0.06%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9b8538
#   0.06%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9f77c6
#   0.06%  cciQueuePerf  [kernel]          [k] 0xffffffff9e8d5488
#   0.06%  cciQueuePerf  [kernel]          [k] 0xffffffff9ec57299
#   0.06%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9c20ee
#   0.06%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9f7605
#   0.04%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9b99ea
#   0.04%  cciQueuePerf  cciQueuePerf      [.] malloc@plt
#   0.04%  cciQueuePerf  [kernel]          [k] 0xffffffff9e9c21be

function generateData() {
    echo "
10 2.000000 1.000000
100 8.000000 7.000000
1000 73.000000 50.000000
10000 540.000000 572.000000
100000 6301.000000 4186.000000
1000000 59446.000000 46575.000000
5000000 258294.000000 193248.000000
10000000 415592.000000 389588.000000
" > /tmp/_
}

function doPlot() {
    echo "
set ytics font ',6'
set xtics font ',6'
set ylabel 'time (micro seconds)'
set xlabel 'numbers of ints'
plot '/tmp/_' u 1:2 t 'enqueue' w l,\
'' u 1:3 t 'dequeue' w l
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
