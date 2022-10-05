#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **LeMatriz(char *nome, int *m, int *n)
{
  FILE *fp = fopen(nome, "r");
  double **Matriz;
  int i, j;

  fscanf(fp, "%d %d", m, n);
  Matriz = (double **)malloc(*m * sizeof(double *));
  for (i = 0; i < *m; i++)
    Matriz[i] = malloc(*n * sizeof(double));

  for (i = 0; i < *m; i++) {
    for (j = 0; j < *n; j++)
      fscanf(fp, "%lf", &Matriz[i][j]);
  }
  return Matriz;
}

double *LeVetor (char *nome, int *m)  {  
  FILE *fp = fopen(nome, "r"); 
  double *Vetor;
  int i, f;

  f = fscanf(fp, "%d", m); 
  Vetor = (double *) malloc( *m* sizeof(double) );
  for (i = 0; i<*m; i++) f = fscanf(fp,"%lf", &Vetor[i]);
 
  return Vetor;
}

void ImprimeMatriz (double **M, int m, int n) {
  int i, j;

  for (i = 0; i < m; i++) {
    printf("| ");
    for (j = 0; j < n; j++) printf ("%9.5lf\t", M[i][j]);
	  puts (" |");
  }
} 

void ImprimeVetor (double *V, int m) {
  int i;
   
  printf("( "); 
  for (i = 0; i < m; i++) printf ("%9.5g\t", V[i]);
	puts (")");
} 

double NormaVetor(double *v, int m, int p) {
  double norma=0;
  int i;

  if (p) {
    for ( i=0; i<m; i++) norma += pow(fabs(v[i]),p);
    norma = pow(norma, 1./p);
  }
  else {
    for ( i=0; i<m; i++) norma = (fabs(v[i])>norma) ? fabs(v[i]):norma;
  }
  return norma;
}

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

double Gauss(double **Matriz, int m, int n, double *x0, int p){
    int i,j;
    double dx = 0,*x, xa, norma;

    x = (double *)  malloc( m*sizeof(double) );
    for(i=0; i<m; i++) x[i] = x0[i];
    dx = 0;
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
    dx = NormaVetor(x, m, p);
    free(x); 
    return dx;
}

double Relaxacao(double **Matriz, int m, int n, double *x0, double omega, int p){
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
      x0[i]=(1-omega)*xa+omega/Matriz[i][i]*x0[i];
    }
    for(i=0; i<m; i++) x[i]-=x0[i]; 
    norma = NormaVetor(x, m, p); 
    return norma;
}

int main(int argc, char **argv) {
  double **M, *v, dx, tolerance=1e-5;
  int m, n, l, i, it=0,  p=0;

  M = LeMatriz(argv[1], &m, &n);
  v = LeVetor(argv[2], &l);

  do{ 
     it++;
     dx = Relaxacao(M, m, n, v, 1.0625, p); 
     printf("%d %8.4g \n", it,dx);
  } while (dx > tolerance);
  ImprimeVetor(v,m);
  puts(""); 
  return 0;
}