#include <stdio.h>
#include <stdlib.h>

double **LeMatriz(char nome[20], int *m, int *n) {
 FILE *arq;
 int i,j;
 double **a;     

 arq = fopen(nome, "r"); 
 fscanf(arq, "%d", m); 
 fscanf(arq, "%d", n); 
 a=(double **) malloc(*m*sizeof(double *)); 
 for (i=0; i<*m; i++) a[i]=(double *) malloc((*n)*sizeof(double)); 
    
 for (i=0; i<*m; i++) { 
   for (j=0; j<*n; j++) {
     fscanf(arq, "%lf", &a[i][j]);
   }
 }    
 return a;
} 

void **TrocaLinha(double **k, double **l) {
  double *temp; 
  
  temp = *k;
  *k = *l;
  *l = temp;
}

double **EliminaGauss(double **M, int *m, int *n) {
  int i,j,k,k2; 
  double l; 
  
  for(k=0; k<*n-1; k++) {
    if (M[k][k]==0) {
      k2 = k+1;  
      while ((M[k2][k]==0)&&(k2<*m)) k2++;
      if (k2 == *m) {
        puts ("Sistema sem Solução!!!!");
        return M; 
      }
      TrocaLinha(&M[k], &M[k2]);
    }
    for(i=k+1; i<=*m-1; i++) {
      l = M[i][k]/M[k][k]; 
      for(j=0; j<*n; j++) {
        M[i][j] = l * M[k][j] - M[i][j];
      }
    }
  }
  return M; 
}

int main() {
  double **M;
  int i, j, m, n;
  FILE *arq; 
  
  M = LeMatriz("matriz.dat", &m, &n);
  M = EliminaGauss(M, &m, &n); 


  for (i=0; i<m; i++) { 
   for (j=0; j<n; j++) {
     printf("%lf ", M[i][j]);
   }
   puts("");
  }    

  return 0;  
}  
