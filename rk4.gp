reset
set terminal qt size 800,600 font "Letters for Learners, 16" 

# "KG Midnight Memories, 18" 

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "black" behind

set border lc rgb 'white'
set style line 1 lc rgb '#FFFFFFFF'  lw 1 ps 0.5
set style line 2 lc rgb '#DDFFFFFF'  lw 1 ps 0.5
set log
set grid mxtics mytics xtics ytics  ls 1,  ls 2  
set key left top reverse tc rgb "white"
set format y "10^{%T}" 
set format x "10^{%T}"

set xlabel "h" tc rgb 'white'
set ylabel "erro" tc rgb 'white'

plot "dados.dat" u 1:2 w lp pt 5  ps 2 lc rgb "yellow" t"Euler", \
     "dados.dat" u 1:3 w lp pt 7  ps 2 t"Euler Mod", \
     "dados.dat" u 1:4 w lp pt 13 ps 2 t"RK4"
