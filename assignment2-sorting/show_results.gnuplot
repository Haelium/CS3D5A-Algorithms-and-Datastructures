set datafile separator ","
set terminal png

set xlabel "Size of array sorted" font "verdana, 12"
set ylabel "Time to sort (in ???)" font "verdana, 12"
set grid
set key top left

set output "mr_plotty.png"
plot "quicksort_results.csv" using 1:2, "heapsort_results.csv" using 1:2

