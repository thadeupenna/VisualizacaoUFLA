#include "metnumii.h"

double DotProduct(double *a, int m, double *b) {
  double dot=0;
  int i;

  for(i=0; i<m; i++) {
    dot += a[i]*b[i];
  }
  return dot;
}


double *GradienteConjugado(double **A, int m, double *x, double *r, double *d) {
  int i;
  double lambda, *x1;

  x1 = (double *) malloc( m*sizeof(double) );
  x1 = MatrizxVetor(A,m,m,d);
  lambda = DotProduct (r,m,d)/DotProduct(d,m,x1);
  for(i=0; i<m; i++) x1[i] = x[i] + lambda*d[i];

  return x1;
}

double *Updated(double **A, double *d, int m, double *r) {
  int i;
  double *Ad, beta;

  Ad = (double *) malloc( m*sizeof(double) );
  Ad = MatrizxVetor(A, m, m, d);
  beta = DotProduct (r,m,Ad)/DotProduct(d,m,Ad);
  for (i=0; i<m; i++) Ad[i] = r[i] - beta*d[i];

  return Ad;
}

int main (int argc, char **argv) {
  int m, n, i, iterations=0;
  double **A, *x0, *r0, *d0, **Coef, *b, tolerance=1e-8;

  A = LeMatriz(argv[1], &m, &n);
  SeparaSistema(A, m, n, &Coef, &b);
  x0 = LeVetor(argv[2], &m); 

  r0 = (double *) malloc( m*sizeof(double) );
  d0 = (double *) malloc( m*sizeof(double) );
  r0 = MatrizxVetor(Coef, m, n, x0);
  for(i=0; i<m; i++) {
    r0[i] = b[i] - r0[i];
    d0[i] = r0[i];
  }

  while ((NormaVetor(r0, m, 0)>tolerance)&&(iterations<180)) {

    x0 = GradienteConjugado(A, m, x0, r0, d0);

    r0 = MatrizxVetor(A, m, m, x0);
    for(i=0; i<m; i++) r0[i] = b[i] - r0[i];

    d0 = Updated(Coef, d0, m, r0);
    iterations++;
    printf("%d \t%g\t" ,iterations, NormaVetor(r0, m, 0) );
    for (i=0; i<m; i++) printf("x[%d]=%.6lf   ",i,x0[i]);
    puts("");
  }
}
