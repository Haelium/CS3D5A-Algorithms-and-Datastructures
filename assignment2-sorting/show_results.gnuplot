set datafile separator ","
set terminal png

set grid
set key top left
set format x "%g"
set xlabel "Size of array sorted" font "verdana, 12"

set ylabel "Time to sort (in probes)" font "verdana, 12"
set output "mr_probey.png"
plot "quicksort_probe_results.csv" using 1:2, "heapsort_probe_results.csv" using 1:2

set ylabel "Time to sort (in clock cycles)" font "verdana, 12"
set output "mr_clocky.png"
plot "quicksort_clock_results.csv" using 1:2, "heapsort_clock_results.csv" using 1:2
