set datafile separator ","
set terminal png
set output "gnuplot_output.png"
plot "lp_results.csv" using 1:2, "dh_results.csv" using 1:2
