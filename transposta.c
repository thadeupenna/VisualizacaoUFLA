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

double **Transposta(double **M, int m, int n) {
  double **T; 
  int i, j;

  T = (double **) malloc( m * sizeof(double *) );
  for (i = 0; i < m; i++)  T[i] = malloc (n * sizeof (double));

  for (i = 0; i < m; i++)
  for (j = 0; j < n; j++) 
  T[i][j] = M[j][i];

  return T;
}

int ComparaMatrizes(double **M, double **N, int m1, int m2) {
  int i, j, difer=0;
  double tol=1e-15;

  for (i = 0; i < m1; i++) 
  for (j = 0; j < m2; j++) 
  if ( fabs(M[i][j] - N[i][j]) > tol) {
    difer++;
    break;
  }
  return difer; 
}

int Comparamemcmp(double **M, double **C, int m1, int m2){
  int i, s = 0;

  for(i = 0; i<m1; i++){
    s += memcmp(M[i], C[i], m2*sizeof(double));
    if(s!=0) break;
  }
  return s;
}

int main (int argc, char **argv) {
  double **M, **N, **P1, **P2, **MT, **NT, **MNT;
  int m1, m2, n1, n2, difer; 

  M = LeMatriz (argv[1], &m1, &m2);
  N = LeMatriz (argv[2], &n1, &n2);

  P1 = Produto(M, N, m1, m2, n1, n2);
  P1 = Transposta(P1, m1, n2);

  MT = Transposta(M, m1, m2); 
  NT = Transposta(N, n1, n2);
  MNT = Produto(NT, MT, n2, n1, m2, m1);

  puts("N^T M^T");
  ImprimeMatriz( MNT, m1, n2);
  puts("\n (M.N)^T");
  ImprimeMatriz( P1, m1, n2);  

  difer = Comparamemcmp( MNT, P1, m1, n2); 
  if (difer) puts("Matrizes diferentes");
  else puts("Matrizes iguais");
  
  return 0;
}