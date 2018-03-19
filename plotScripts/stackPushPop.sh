#!/usr/bin/env bash

#Samples: 1K of event 'cycles', Event count (approx.): 1642386508
#Overhead  Command       Shared Object     Symbol                                         ▒
#  23.28%  cciStackPerf  cciStackPerf      [.] newInt                                     ▒
#  17.84%  cciStackPerf  cciStackPerf      [.] AlPopBack                                  ▒
#  14.15%  cciStackPerf  libc-2.23.so      [.] __memcpy_avx_unaligned                     ▒
#  12.83%  cciStackPerf  cciStackPerf      [.] AlEmplaceBack                              ▒
#   8.99%  cciStackPerf  [kernel]          [k] 0xffffffff9ec57297                         ▒
#   6.69%  cciStackPerf  cciStackPerf      [.] CCIStackPush                               ▒
#   5.45%  cciStackPerf  cciStackPerf      [.] CCIStackPop                                ▒
#   5.27%  cciStackPerf  cciStackPerf      [.] doPush                                     ▒
#   2.76%  cciStackPerf  cciStackPerf      [.] doPop                                      ▒
#   0.44%  cciStackPerf  [kernel]          [k] 0xffffffff9f0d7ac0                         ◆
#   0.21%  cciStackPerf  [kernel]          [k] 0xffffffff9e9b77a2                         ▒
#   0.16%  cciStackPerf  [kernel]          [k] 0xffffffff9f0d6540                         ▒
#   0.15%  cciStackPerf  [kernel]          [k] 0xffffffff9e9ed0ec                         ▒
#   0.15%  cciStackPerf  [kernel]          [k] 0xffffffff9e9b9e7c                         ▒
#   0.13%  cciStackPerf  [kernel]          [k] 0xffffffff9ec57299                         ▒
#   0.10%  cciStackPerf  [kernel]          [k] 0xffffffff9e9b9e9c                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e8be8b1                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e8be8a6                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9ea2a4                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9ed0d1                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9c217d                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9f0d1180                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9c2c35                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9b7772                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9ed0d8                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e8bcf12                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9e9d99                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e8ba914                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9ed0fb                         ▒
#   0.05%  cciStackPerf  libc-2.23.so      [.] __GI___munmap                              ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9ea2ef2b                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e8c7ca2                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9b9e88                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e8be6aa                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9b7763                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9e9d10                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9ea00026                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9d67a8                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9b8fa6                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9f77c8                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e9b7c93                         ▒
#   0.05%  cciStackPerf  [kernel]          [k] 0xffffffff9e803ab8                         ▒
#   0.04%  cciStackPerf  [kernel]          [k] 0xffffffff9e9b7ced

function generateData() {
    echo "
10 4.000000 1.000000
100 5.000000 1.000000
1000 27.000000 7.000000
10000 318.000000 71.000000
100000 2597.000000 716.000000
1000000 21938.000000 7858.000000
5000000 113666.000000 38952.000000
10000000 223533.000000 78076.000000
" > /tmp/_
}

function doPlot() {
    echo "
set ytics font ',6'
set xtics font ',6'
set ylabel 'time (micro seconds)'
set xlabel 'numbers of ints'
plot '/tmp/_' u 1:2 t 'stack push' w l,\
'' u 1:3 t 'stack pop' w l
" > /tmp/_.gnuplot
    gnuplot -p -c /tmp/_.gnuplot
}

generateData
doPlot
