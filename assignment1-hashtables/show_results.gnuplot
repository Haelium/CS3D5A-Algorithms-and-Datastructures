set datafile separator ","
set terminal png

set xlabel "Number of filled buckets"
set ylabel "Average number of collisions while inserting"
set grid
set key left tmargin

set output "lp_with_dh_plot.png"
plot "lp_results.csv" using 1:2, "dh_results.csv" using 1:2

set output "dh_plot.png"
plot "dh_results.csv" using 1:2 lt rgb "#00FF00"
