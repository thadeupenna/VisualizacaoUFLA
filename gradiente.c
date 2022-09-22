#include "metnumii.h"

double DotProduct(double *a, int m, double *b) {
  double dot=0;
  int i;

  for(i=0; i<m; i++) {
    dot += a[i]*b[i];
  }
  return dot;
}

double *Gradiente(double **A, int m, double *x, double *r) {
  int i;
  double lambda, *x1;

  x1 = (double *) malloc( m*sizeof(double) );
  x1 = MatrizxVetor(A, m, m, r);
  lambda = DotProduct (r, m, r)/DotProduct(r, m, x1);
  for(i=0; i<m; i++) x1[i] = x[i] + lambda*r[i];

  return x1;
}

int main (int argc, char **argv) {
  int m, n, i, iterations=0;
  double **A, *x0, *r0, *d0, *b, **Coef, tolerance=1e-8;

  A = LeMatriz(argv[1], &m, &n);
  SeparaSistema(A, m, n, &Coef, &b);
  x0 = LeVetor(argv[2], &m); 
  if (!PositivaDefinida(Coef, m)) {
    puts("'Atenção !! A matriz não é definida positiva."); 
  }
  r0 = (double *) malloc( m*sizeof(double) );
  d0 = (double *) malloc( m*sizeof(double) );
  r0 = MatrizxVetor(Coef, m, n, x0);
  for(i=0; i<m; i++) {
    r0[i] = b[i] - r0[i];
    d0[i] = r0[i];
  }

  while ((NormaVetor(r0, m, 0)>tolerance)&&(iterations<80)) {
    x0 = Gradiente(Coef, m, x0, r0);

    r0 = MatrizxVetor(Coef, m, n, x0);
    for(i=0; i<m; i++) r0[i] = b[i] - r0[i];

    iterations++;
    printf("\n%2d\t %g \t",iterations, NormaVetor(r0, m, 0));
    for (i=0; i<m; i++) printf("%.6g  ",x0[i]);
  }
  puts("");
  return 0;
}