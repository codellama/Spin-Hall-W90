set style data dots
set nokey
set xrange [0: 3.81843]
set yrange [ -6.82185 : 17.38328]
set arrow from  1.00811,  -6.82185 to  1.00811,  17.38328 nohead
set arrow from  2.17218,  -6.82185 to  2.17218,  17.38328 nohead
set arrow from  2.58375,  -6.82185 to  2.58375,  17.38328 nohead
set xtics (" L "  0.00000," G "  1.00811," X "  2.17218," K "  2.58375," G "  3.81843)
 plot "silicon_band.dat"
