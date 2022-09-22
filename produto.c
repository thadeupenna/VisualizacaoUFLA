#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double **LeMatriz (char *nome, int *m, int *n)  {  
  FILE *fp = fopen(nome, "r"); 
  double **Matriz;
  int i, j;

  fscanf(fp, "%d %d", m, n);
  Matriz = (double **) malloc( *m* sizeof(double *) );
  for (i = 0; i < *m; i++)  Matriz[i] = malloc (*n * sizeof (double));

  for (i = 0; i < *m; i++) {
    for (j = 0; j < *n; j++) fscanf(fp,"%lf", &Matriz[i][j]);
  }
  return Matriz;
}

void ImprimeMatriz (double **M, int m, int n) {
  int i, j;

  for (i = 0; i < m; i++) {
    printf("| ");
    for (j = 0; j < n; j++) printf ("%9.5lf\t", M[i][j]);
	  puts (" |");
  }
} 

double **Produto(double **M, double **N, int m1, int m2, int n1, int n2) {
  double **Matriz; 
  int i, j, k;

  Matriz = (double **) malloc( m1 * sizeof(double *) );
  for (i = 0; i < m1; i++)  Matriz[i] = malloc (n2 * sizeof (double));

  if ( m2 != n1 ) {
    puts("Dimensões incompatíveis"); 
    return Matriz;
  }  

  for(i = 0; i < m1; i++) {
    for(j = 0; j < n2; j++) {
      Matriz[i][j] = 0;
      for(k = 0; k < m2; k++) {
        Matriz[i][j] += M[i][k] * N[k][j];
      }
    }
  }  
  return Matriz;
}

int main (int argc, char **argv) {
  double **M, **N, **P;
  int m1, m2, n1, n2; 

  M = LeMatriz (argv[1], &m1, &m2);
  N = LeMatriz (argv[2], &n1, &n2);
  P = Produto(M, N, m1, m2, n1, n2);
  ImprimeMatriz( P, m1, n2);

  return 0;
}