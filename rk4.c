#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double df(double x, double y){
  return 501*exp(x)-500*y;
}

double exato(double x){
  return exp(x)-exp(-500*x);
}


double euler(double x, double ye, double h){
  return h*df(x, ye);
}

double eulermod(double x, double ym, double h){
  double xi_1, yi_1;
  xi_1 = x+h;
  yi_1 = ym+h*df(x,ym);
  return ((h/2)*(df(x,ym) + df(xi_1, yi_1)));
}

double rk4(double x, double yrk, double h){
  double k1, k2, k3, k4;

   k1 = df(x, yrk);
   k2 = df(x+h/2, yrk + h*k1/2);
   k3 = df(x+h/2, yrk + h*k2/2);
   k4 = df(x+h, yrk + h*k3);

  return (k1+2*k2+2*k3+k4)*h/6;
}

int main (int argc, char **argv) {
  
  double h = 1,x,ym,ye,yrk,ex;
  int i;

  for(i=0; i<14; i++) {
    ye=ym=yrk=1;
    h/=2;
    for (x=0;x<=1;x+=h) {
      ex = exato(x+h);
      ye +=euler(x,ye,h);
      ym +=eulermod(x,ym,h);
      yrk+=rk4(x,yrk,h);
    }
    printf("%g ",h);
	  printf("%g %g %g\n", fabs(ye-ex),fabs(ym-ex),fabs(yrk-ex));
  }
  return 0;
} 