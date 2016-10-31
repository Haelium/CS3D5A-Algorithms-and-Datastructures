set datafile separator ","
set terminal png

set xlabel "Number of filled buckets" font "verdana, 17"
set ylabel "Mean collisions per insertion" font "verdana, 17"
set grid
set key top left

set output "lp_with_dh_plot.png"
plot "lp_results.csv" using 1:2, "dh_results.csv" using 1:2

set output "dh_plot.png"
plot "dh_results.csv" using 1:2 lt rgb "#00FF00"

set logscale y
set output "lp_with_dh_plot_log.png"
plot "lp_results.csv" using 1:2, "dh_results.csv" using 1:2

set output "dh_plot_log.png"
plot "dh_results.csv" using 1:2 lt rgb "#00FF00"