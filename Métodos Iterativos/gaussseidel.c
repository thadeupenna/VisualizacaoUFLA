#include "metnumii.h"

double Gauss(double **Matriz, int m, int n, double *x0, int p){
    int i,j;
    double dx = 0,*x, xa, norma;

    x = (double *)  malloc( m*sizeof(double) );
    for(i=0; i<m; i++) x[i] = x0[i];
    norma = 0;
    for(i=0; i<m; i++) {
      xa = x0[i];
      x0[i] = Matriz[i][n-1];
      for(j=0; j<m; j++) {
        if (i == j) continue;
        x0[i] -= Matriz[i][j]*x0[j];
      }
      x0[i]/=Matriz[i][i];
    }
    for(i=0; i<m; i++) x[i]-=x0[i]; 
    norma = NormaVetor(x, m, p);
    free(x); 
    return norma;
}

