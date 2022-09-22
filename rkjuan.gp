reset
plot cos(x)+(sqrt(2)-1)*sin(x)
replot 'dadosj.dat' t "ys" w lp , 'dadosj.dat' u 1:3 t "ya" w lp, 'dadosj.dat' u 1:4 t "yb" w lp
