#File to plot a colour-mapped Bandstructure
set palette defined ( 0 "blue", 3 "green", 6 "yellow", 10 "red" )
unset ztics
unset key
# can make pointsize smaller (~0.5). Too small and nothing is printed
set pointsize 0.8
set grid xtics
set view 0,0
set xrange [0:  7.81010]
set yrange [  1.81741: 36.04804]
set xtics (" G "  0.00000," X "  1.74047," W "  2.61071," L "  3.84141," G "  5.34870," K "  7.81010)
splot "copper_band.dat" u 1:2:3 w p pt 13 palette
#use the next lines to make a nice figure for a paper
#set term postscript enhanced eps color lw 0.5 dl 0.5
#set pointsize 0.275
