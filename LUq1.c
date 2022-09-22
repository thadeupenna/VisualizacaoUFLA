#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double **LeMatriz(char *nome, int *m, int *n){
  FILE *fp = fopen(nome, "r");
  int i, j;
  double **Matriz;

  fscanf(fp, "%d %d", m, n);
  Matriz = (double **) malloc(*m *sizeof(double *));
  for (i=0; i<*m; i++){
      Matriz[i] = (double *) malloc(*n *sizeof(double));
  }
  for (i=0; i<*m; i++){
    for (j=0; j<*n; j++){
      fscanf(fp, "%lf", &Matriz[i][j]);
    }
    puts("");
  }
  return Matriz;
}

void ImprimirMatriz(double **Matriz, int nl, int nc){
  int i, j;
  for (i=0; i<nl; i++){
    for (j=0; j<nc; j++) printf("%6.4g ", Matriz[i][j]);
    puts("");
  }
}

void TrocaLinha(double **k, double **l){
  double *temp;

  temp = *k;
  *k = *l;
  *l = temp;
}

double **MatrizxMatriz(double **A, int m, int n, double **B, int p, int q){
  int i, j, k;
  double **M;

  if(n!=p) puts("Erro na multiplicação");

  M=malloc(m*sizeof(double *));
  for(i=0; i<m; i++) M[i]=malloc(q*sizeof(double));

  for(i=0; i<m; i++){
    for(j=0; j<q; j++){
      M[i][j]=0;
      for(k=0; k<p; k++) M[i][j] += A[i][k]*B[k][j];
    }
  }
  return M;
}

void **LUPivot(double **M, double ***L, double ***U, double **b, int m, int n){
  int i, j, k, p;
  double lbd, pivot;

  *L = calloc(m, sizeof(double *));
  for(i=0; i<m; i++) (*L)[i] = calloc(m, sizeof(double));

  *U = malloc(m*sizeof(double *));
  for(i=0; i<m; i++) (*U)[i] = malloc(m*sizeof(double));

  *b = malloc(m*sizeof(double));
  for(i=0; i<m; i++) (*b)[i] = M[i][n-1];

  for(i=0; i<m; i++){
    (*L)[i][i] = 1;
    for(j=0; j<m; j++){
      (*U)[i][j] = M[i][j];
    }
  }

  for(j=0; j<m-1; j++){
    pivot = (*U)[j][j];
    p=0;

    for(i=j+1; i<m; i++){
      if(fabs((*U)[i][j])>pivot){
        pivot=fabs((*U)[i][j]);
        p=i;
      }
    }

    if(p){
      TrocaLinha(&(*U)[p], &(*U)[j]);
      lbd=(*b)[p];
      (*b)[p]=(*b)[j];
      (*b)[j]=lbd;
    }

    for(i=j+1; i<m; i++){
      lbd=(*L)[i][j] = (*U)[i][j]/(*U)[j][j];
      for(k=j; k<m; k++) (*U)[i][k] -= lbd*(*U)[j][k];
    }

  }
}

double *SubstituicaoDireta(double **M, int m, double *b){
  double *y, sum;
  int i, j;

  y=malloc(m*sizeof(double));

  for(i=0; i<m; i++){
    sum=0;
    for(j=i-1; j>=0; j--){
      sum += M[i][j]*y[j];
    }
    y[i] = (b[i]-sum)/M[i][i];
  }
  return y;
}

double *SubstituicaoReversa(double **M, int m, double *b){
  double *y, sum;
  int i, j;

  y=malloc(m*sizeof(double));

  for(i=m-1; i>=0; i--){
    sum=0;
    for(j=i+1; j<=m-1; j++){
      sum += M[i][j]*y[j];
    }
    y[i] = (b[i]-sum)/M[i][i];
  }
  return y;
}

int Compara(double **M, double **C, int nl){
  int i, j, s=0;
  for(i=0; i<nl; i++){
    for(j=0; j<nl; j++){
      s*=memcmp(M[i], C[j], nl*sizeof(double)); // Se s = 0, então as linhas são iguais
      if(s=0) break;
    }
  }
  return s;
}

double *MatrizxVetor(double **M, double *x, int m, int n){
  int i, j, k;
  double *r;

  r = malloc(m*sizeof(double *));

  for(i=0; i<m; i++){
    for(j=0; j<n; j++){
      r[i]+=M[i][j]*x[j];
    }
  }
  return r;
}

int VerificaSistema(double **M, int m, int n, double *x, double *b){
  if(memcmp(MatrizxVetor(M,x,m,n), b, m*sizeof(double)))
    return 1;
  else 
    return 0;
}

void ImprimeVetor(double *v, int j){
  int i;
  for(i=0; i<j; i++) printf("bd[%d] = %g\n", i, v[i]);
}

int main(int argc, char **argv) {
  int m, n, i;
  double **M, **L, **U, *b, *v, *x;

  M=LeMatriz(argv[1], &m, &n);
  LUPivot(M, &L, &U, &b, m, n);

  v = SubstituicaoDireta(L,m,b);
  b = SubstituicaoReversa(U,m,v);
  ImprimeVetor(b, m);

  return 0;
}