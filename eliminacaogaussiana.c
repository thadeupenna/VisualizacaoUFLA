#include <stdio.h>
#include <stdlib.h>

double **LeMatrix(int m, int n) {
  double **M;
  int i,j;
  
  M = malloc ( m*sizeof(double *) );
  for ( i = 0; i < m; i++ ) M[i] = malloc( m*sizeof(double));
  
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
        scanf("%lf", &M[i][j]);
    }  
  }
  return M;
}

void ImprimeMatriz(double **M, int m, int n) {
  int i,j;
  
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("%5.2lf ",M[i][j]);
    }
    puts("");
  }
  puts("");
}

double **TrocaLinhas(double **M,int m, int n, int i, int j) {
  double tmp;
  int k;
  
  for (k=0; k<n; k++) {
    tmp = M[i][k];
    M[i][k] = M[j][k];
    M[j][k] = tmp; 
  }
  return M;
}

double **MultLinha(double **M, int m, int n, int i, int j, double lbd) {
  
  for (int k=0; k<n; k++) M[j][k] -= M[i][k]*lbd;
  return M;
}

double **Triangulariza( double **M, int m, int n) {
  int i,j,p;

  for(i=0; i<m-1; i++) {
    if (M[i][i] == 0) {
      p = i; 
      do {
        p++; 
      } while ((M[p][i] == 0)&&(p<m));
      M = TrocaLinhas(M,m,n,i,p);
      if (M[i][i]==0) {
        puts("Sistema sem solução");
        exit(1); 
      }  
    }  
    for(j=i+1; j<m; j++) {
      lbd = M[j][i]/M[i][i];
      M = MultLinha(M,m,n,i,j,lbd);
    }
  }
  return M;   
}

int main(int argc, char **argv)
{
  int m,n,i,j,p;
  double **M, lbd;
  
  m = atoi(argv[1]);
  n = atoi(argv[2]);
  M = LeMatrix(m,n);
  ImprimeMatriz(M,m,n);
  M = Triangulariza(M,m,n);
  ImprimeMatriz(M,m,n);
  return 0;
}
