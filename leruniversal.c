#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

  for (i = 0; i < *m; i++)
  {
    for (j = 0; j < *n; j++)
      fscanf(fp, "%lf", &Matriz[i][j]);
  }
  return Matriz;
}

void ImprimeMatriz(double **M, int m, int n)
{
  int i, j;

  for (i = 0; i < m; i++)
  {
    printf("| ");
    for (j = 0; j < n; j++)
      printf("%9.5lf\t", M[i][j]);
    puts(" |");
  }
}

void TrocaLinhas(double **k, double **l)
{
  double *temp;

  temp = *k;
  *k = *l;
  *l = temp;
}

double **MatrizxMatriz(double **M1, int m1, int n1, double **M2, int m2, int n2)
{
  int i, j, k;
  double **P, sum;

  if (n1 != m2)
  {
    puts("Não é possível multiplicar.");
    return M1;
  }

  P = malloc(m1*sizeof(double *));
  for (i = 0; i < m1; i++)
    P[i] = malloc(n2*sizeof(double));

  for (i = 0; i < m1; i++)
  {
    for (j = 0; j < n2; j++)
    {
      sum = 0;
      for (k = 0; k < n1; k++)
        sum += M1[i][k] * M2[k][j];
      P[i][j] = sum;
    }
  }
  return P;
}

int ComparaMatriz(double **M, double **N, int m , int n) {
  int i,diferente=0;

  for(i=0; i<m; i++)  diferente += memcmp(M[i], N[i], n*sizeof(double));

  return diferente;
}

double **LUSist(double **M, double ***L, double ***U, int m, int n)
{
  int i, j, k, p;
  double lbd, pivot, **b;

  /*  Alocacao de memória
   */
  *L = calloc(m, sizeof(double *));
  for (i = 0; i < m; i++) (*L)[i] = calloc(m, sizeof(double));

  *U = malloc(m * sizeof(double *));
  for (i = 0; i < m; i++) (*U)[i] = malloc(m * sizeof(double));

  b = malloc(m * sizeof(double *));
  for (i = 0; i < m; i++)  { 
    b[i] = malloc(sizeof(double));
    b[i][0] = M[i][n - 1];
  } 

  for (i = 0; i < m; i++)  { 
    for (j = 0; j < m; j++)
    {
      (*U)[i][j] = M[i][j];
    }
  }

  // Loop em colunas
  for (j = 0; j < m - 1; j++)
  {
    /*  Pivotamento */
    pivot = (*U)[j][j];
    p = 0;

    for (i = j + 1; i < m; i++)
    {
      if (fabs((*U)[i][j]) > pivot)
      {
        pivot = fabs((*U)[i][j]);
        p = i;
      }
    }

    if (p)
    {
      TrocaLinhas(&(*U)[p], &(*U)[j]);
      TrocaLinhas(&(*L)[p], &(*L)[j]);
      lbd = b[p][0];
      b[p][0] = b[j][0];
      b[j][0] = lbd;
    }

    /*  Eliminação Gaussiana 
     */
    for (i = j + 1; i < m; i++)
    {
      lbd = (*U)[i][j] / (*U)[j][j];
      for (k = j; k < m; k++)
        (*U)[i][k] -= lbd * (*U)[j][k];
      (*L)[i][j] = lbd;   
    }
  }
  for (i=0; i<m; i++) (*L)[i][i] = 1;
  return b;
}

double **SubstituicaoReversa(double **M, int m, double **b)
{
  double **v, sum;
  int i, j;

  v = malloc(m * sizeof(double *));
  for (i = 0; i < m; i++)   
    v[i] = malloc(sizeof(double));


  for (i = m - 1; i >= 0; i--) {
    sum = 0;
    for (j = i + 1; j <= m - 1; j++) {
      sum += M[i][j] * v[j][0];
    }
    v[i][0] = (b[i][0] - sum) / M[i][i];
  }
  return v;
}

double **SubstituicaoDireta(double **M, int m, double **b) {
  double **v, sum;
  int i, j;

  v = malloc(m* sizeof(double*));
  for (i=0; i<m; i++) 
    v[i] = malloc(sizeof(double));

  for (i=0; i<m; i++) {
    sum =0;
    for (j=i-1; j>=0; j--)  {
      sum += M[i][j] * v[j][0]; 
    }  
    v[i][0] = (b[i][0] - sum) / M[i][i];
  }
  return v;
}

double TestaMatriz(double **M, double m, double n, double **Raizes) {
  
}

int main(int argc, char **argv) {
  double **M, **N, **Mod, **b, **L, **Raizes, **U, **v, erro;
  int m, n, r, s; 
  
  M = LeMatriz(argv[1], &m, &n);
  b = LUSist(M, &L, &U, m, n);
  ImprimeMatriz(L, m, m);puts("<-L");
  ImprimeMatriz(U, m, m);puts("<-U\n");

  Mod = MatrizxMatriz(L,m,m,U,m,m); 
  ImprimeMatriz(Mod, m, m);puts("<-M");
  v = SubstituicaoDireta(L,m,b);
  Raizes = SubstituicaoReversa(U,m,v);
  puts("\n\n");
  ImprimeMatriz(b, m, 1);
  erro = TestaMatriz(M,m,n,Raizes);
  v = MatrizxMatriz(M, m, m, b, m, 1); 
  ImprimeMatriz(v, m, 1);
  return 0;
}
