set datafile separator ","
set xlabel "Krok k"
set ylabel "Wyjście / Sterowanie"
set grid
set key outside right

set terminal wxt size 1200,800

plot "wyniki_dmc_A.csv" using 1:2 with lines title "A: y(k)" lw 2, \
     "wyniki_dmc_A.csv" using 1:3 with lines title "A: u(k)" lw 2, \
     "wyniki_dmc_B.csv" using 1:2 with lines title "B: y(k)" lw 2, \
     "wyniki_dmc_B.csv" using 1:3 with lines title "B: u(k)" lw 2, \
     "wyniki_dmc_C.csv" using 1:2 with lines title "C: y(k)" lw 2, \
     "wyniki_dmc_C.csv" using 1:3 with lines title "C: u(k)" lw 2, \
     1.0 with lines title "Wartość zadana" lw 2 dt 2

pause -1 "Naciśnij Enter żeby zamknąć..."