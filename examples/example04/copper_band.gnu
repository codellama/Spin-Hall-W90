set style data dots
set nokey
set xrange [0: 7.81010]
set yrange [  1.81741 : 36.04804]
set arrow from  1.74047,   1.81741 to  1.74047,  36.04804 nohead
set arrow from  2.61071,   1.81741 to  2.61071,  36.04804 nohead
set arrow from  3.84141,   1.81741 to  3.84141,  36.04804 nohead
set arrow from  5.34870,   1.81741 to  5.34870,  36.04804 nohead
set xtics (" G "  0.00000," X "  1.74047," W "  2.61071," L "  3.84141," G "  5.34870," K "  7.81010)
 plot "copper_band.dat"
