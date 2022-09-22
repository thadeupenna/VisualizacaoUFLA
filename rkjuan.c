#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double fl(double x, double y, double yl){ return yl;}
double fll1(double x,double y, double yl) { return (-y); }
double fll2(double x,double y,double yl){return(-y);}

double *RK(double fll(),double x0, double x1, double y0,double y0l,double *ult, double h)
{
  double f0,f0l,y,yl,x,k11,k21,k31,k41,k12,k22,k32,k42,*p;
  int n,i=0;
  n= (x1-x0)/h;//valor do tamanho do vetor para alocar os valores
  // printf("n=%d\n",n);
  p=(double*)malloc((n+2)*sizeof(double));
  f0 = y0;
  f0l= y0l;
  p[0] = y0;
  for(x=x0;x<x1;x+=h)
  {
    //printf("%g %g \n",x,y);
    k11=fl(x,f0, f0l);
    k12=fll(x,f0,f0l);
    k21=fl (x+h/2,f0+k11*h/2,f0l+k12*h/2);
    k22=fll(x+h/2,f0+k11*h/2,f0l+k12*h/2);
    k31= fl(x+h/2,f0+k21*h/2,f0l+k22*h/2);
    k32=fll(x+h/2,f0+k21*h/2,f0l+k22*h/2);
    k41=fl(x+h,f0+k31*h,f0l+k32*h);
    k42=fll(x+h,f0+k31*h,f0l+k32*h);
    y= f0 +(k11+2*k21+2*k31+k41)*h/6;
    f0=y;
    yl=f0l+(k12+2*k22+2*k32+k42)*h/6;
    f0l=yl;
    i++;
    p[i] = y;
  }
  *ult =yl;
  // printf("\n");
  return p;
}

int main(int argc, char **argv) {
  double x,x0,x1,y0,h,y1,*a,*b,ys,ulta,ultb,ya,yb;
  int i=0,n;
  
  x0 = atof(argv[1]);
  x1 = atof(argv[2]);
  y0 = atof(argv[3]);
  y1= atof(argv[4]);
  h= atof(argv[5]);//valor de h lido na main para ter controle
  n = (x1-x0)/h;
  a=RK(fll1,x0,x1,y0,0,&ulta,h);
  b=RK(fll2,x0,x1,0,1,&ultb,h);
  ys=y0;
  for(x=x0;x<=x1;x+=h){
    printf("%g %g %g %g\n",x,ys,a[i],b[i]);
    ya = a[i];
    yb= b[i];
    i++;
    ys= ya+(y1-a[n-1])*(yb)/b[n-1];
  }
  
  //intervalo de 0 a 2, y0=0.5
  /*Euler(f,x0,x1,y0,h); puts("\n");
  EulerMod(f,x0,x1,y0,h); puts("\n");
  PM(f,x0,x1,y0,h);*/
}