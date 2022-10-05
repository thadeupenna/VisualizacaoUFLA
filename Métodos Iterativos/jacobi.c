#include "metnumii.h"

double Jacobi(double **Matriz, int m, int n, double *x0, int p) {
    int i,j;
    double *x,dx; 

    x = (double *)  malloc( m*sizeof(double) );

    for(i=0; i<m; i++) {
      x[i] = Matriz[i][n-1];
      for(j=0; j<m; j++) {
        if (i == j) continue;
        x[i] -= Matriz[i][j]* x0[j];
      }
      x[i]/=Matriz[i][i];
    }
    for( i=0; i<m; i++) {
      dx = x0[i];
      x0[i] = x[i];
      x[i] -= dx; 
    }
    dx = NormaVetor( x, m, p);   
    free(x);
    return dx;
}