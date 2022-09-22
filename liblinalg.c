#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double **LeMatrix (char *nome, int *m, int *n)  {  
  FILE *fp = fopen(nome, "r"); 
  double **Matriz;
  int i, j;

  fscanf(fp, "%d %d", m, n);
  Matriz = (double **) malloc( *m* sizeof(double *) );
  for (i = 0; i<*m; i++)  Matriz[i] = malloc (*n * sizeof (double));

  for (i = 0; i<*m; i++) {
    for (j = 0; j<*n; j++) fscanf(fp,"%lf", &Matriz[i][j]);
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

void ImprimeVetor (double *V, int m) {
  int i;
   
  printf("( "); 
  for (i = 0; i < m; i++) printf ("%9.5g\t", V[i]);
	puts (")");
} 

void TrocaLinhas (double **k, double **l) { 
  double *temp;
 
  temp = *k;
  *k = *l;
  *l = temp;
}

void LUSist(double **M, double ***L, double ***U, double **b, int m, int n) {
  int i, j, k, p;
  double lbd, pivot;
 
/*  Alocacao de memória
*/ 
  *L = calloc (m, sizeof (double *));
  for (i = 0; i < m; i++)  (*L)[i] = calloc (m, sizeof (double ));

  *U = malloc (m * sizeof (double *));
  for (i = 0; i < m; i++)  (*U)[i] = malloc (m * sizeof (double));
 
  *b = malloc (m * sizeof(double));
  for(i = 0; i < m; i++) (*b)[i] = M[i][n-1]; 

/* Inicializacao 
*/
  for(i=0; i<m; i++) {
    (*L)[i][i] = 1;
    for(j=0; j<m; j++) {
      (*U)[i][j] = M[i][j];
    }
  }  

// Loop em colunas
  for (j = 0; j < m - 1; j++) {
/*  Pivotamento
*/
    pivot=(*U)[j][j];
    p = 0;

    for (i=j+1; i<m; i++) {
      if ( fabs((*U)[i][j]) > pivot) {
        pivot = fabs((*U)[i][j]); 
        p = i; 
      }
    } 

    if (p) { 
      TrocaLinhas(&(*U)[p], &(*U)[j]); 
      lbd   = (*b)[p];
      (*b)[p] = (*b)[j];
      (*b)[j] = lbd; 
    }

/*  Escalonamento 
*/  
    for (i = j + 1; i < m; i++) {
      lbd = (*L)[i][j] = (*U)[i][j] / (*U)[j][j];
      for(k=j; k<m; k++) (*U)[i][k] -= lbd*(*U)[j][k];
    }   
  }
}

double *SubstituicaoReversa(double **M, int m, double *b) {
  double *v, sum;
  int i, j;

  v = malloc(m* sizeof(double));

  for (i=m-1; i>=0; i--) {
    sum =0;
    for (j=i+1; j<=m-1; j++)  {
      sum += M[i][j]*v[j]; 
    }  
    v[i] = (b[i] - sum)/M[i][i];
  }
  return v;
}

double *SubstituicaoDireta(double **M, int m, double *b) {
  double *v, sum;
  int i, j;

  v = malloc(m* sizeof(double));

  for (i=0; i<m; i++) {
    sum =0;
    for (j=i-1; j>=0; j--)  {
      sum += M[i][j]*v[j]; 
    }  
    v[i] = (b[i] - sum)/M[i][i];
  }
  return v;
}

double **MatrizxMatriz(double **M1, int m1, int n1, double **M2, int m2, int n2) {
  int i,j,k;
  double **P, sum; 

  if (n1 != m2) {
    puts("Não é possível multiplicar.");
    return M1;
  } 

  P = calloc (m1, sizeof (double *));
  for (i = 0; i < m1; i++)  P[i] = calloc (n2, sizeof (double ));
   
  for(i = 0; i < m1; i++) {
    for (j = 0; j < n2; j++) {
      sum = 0;
      for (k =0; k < n1; k++) sum+= M1[i][k] * M2[k][j];
      P[i][j] = sum;
    }
  }

  return P; 
}

double *MatrizxVetor(double **A, int m, int n, double *b){
  double *v; 
  int i,j;  

  v = calloc(n,sizeof(double));
  for(i=0; i<m; i++) {
    for(j=0; j<n; j++) v[i]+= A[i][j]*b[j];
  }

  return v;
}

void SeparaSistema(double **A, int m, int n, double ***Coef, double **b) {
  int i,j; 

  *Coef = malloc (m * sizeof (double *));
  for (i = 0; i < m; i++)  (*Coef)[i] = malloc (m * sizeof (double));
 
  *b = malloc (m * sizeof(double));
  for(i = 0; i < m; i++) (*b)[i] = A[i][n-1]; 

  for (i = 0; i<m; i++) 
  for (j = 0; j<m; j++) (*Coef)[i][j]=A[i][j]; 

}

int CompareMatriz(double **A, double **B, int m, int n) {
  int i,j,k, iguais, linha, linhasiguais = 0;

  for(i=0; i<m; i++) {
    linha = -1;
    for(j=i; j<m; j++) {
      iguais = 0;
      for(k=0; k<n; k++) {
        if (A[i][k] != B[j][k]) continue;
        iguais++;
        if (iguais == n) {
          linha = j;
          break;
        }
      }
      if (linha != -1)  break; 
    }
    if (linha != -1) {
      linhasiguais++;
      TrocaLinhas(&B[i],&B[linha]);
    }  
  }
  return linhasiguais; 
}

double **InversaMatriz(double **A, int m) {
  int i, j, k, p;
  double **Inv, **L, **U, **P, *v, *b, lbd, pivot;

  Inv = calloc (m, sizeof (double *));
  for (i = 0; i < m; i++)  Inv[i] = calloc (m, sizeof (double ));
 
  v = calloc(m, sizeof(double)); 

  L = calloc (m, sizeof (double *));
  for (i = 0; i < m; i++)  L[i] = calloc (m, sizeof (double ));

  U = malloc (m * sizeof (double *));
  for (i = 0; i < m; i++)  U[i] = malloc (m * sizeof (double));
 
  P = calloc (m, sizeof (double *));
  for (i = 0; i < m; i++)  {
    P[i] = calloc (m, sizeof (double));
    P[i][i] = 1 ;
  }

/* Inicializacao 
*/
  for(i=0; i<m; i++) {
    L[i][i] = 1;
    for(j=0; j<m; j++) {
      U[i][j] = A[i][j];
    }
  }  

// Loop em colunas
  for (j = 0; j < m - 1; j++) {
/*  Pivotamento
*/
    pivot=U[j][j];
    p = 0;

    for (i=j+1; i<m; i++) {
      if ( fabs(U[i][j]) > pivot) {
        pivot = fabs(U[i][j]); 
        p = i; 
      }
    } 

    if (p) { 
      TrocaLinhas(&U[p], &U[j]); 
      TrocaLinhas(&P[p], &P[j]);
    }

/*  Escalonamento 
*/  
    for (i = j + 1; i < m; i++) {
      lbd = L[i][j] = U[i][j] / U[j][j];
      for(k=j; k<m; k++) U[i][k] -= lbd*U[j][k];
    }   

  }  /* Fim do loop em colunas */ 


  for (i = 0; i < m; i++) {
    for(j=0; j<m; j++) v[j] = P[j][i];
    v = SubstituicaoDireta(L, m, v); 
    v = SubstituicaoReversa(U, m, v);
    for(j = 0; j < m; j++) Inv[j][i] = v[j];
  }
  free(P);
  return Inv;  
}

int main (int argc, char **argv) {
  int m, n, i, j;
  double **M, **L, **U, **Coef, **Prod, **Inv,  *b, *v;

  if (argc) M = LeMatrix (argv[1], &m, &n);

  SeparaSistema(M, m, n, &Coef, &b);    
  puts(" A  = ");
  ImprimeMatriz(Coef, m, m);  

  Inv = InversaMatriz(Coef, m);
  puts("\n Inv = ");
  ImprimeMatriz(Inv, m, m);  
  // LUPivot(M, &L, &U, &b, m, n); s
  // puts(" L = ");
  // ImprimeMatriz(L, m, m);
  // puts(" U = ");
  // ImprimeMatriz(U, m, m);
  Prod = MatrizxMatriz(Inv, m, m, Coef, m, m); 
  puts("\n Iden = "); 
  ImprimeMatriz(Prod, m, m);

  // puts(" Coef = ");
  // ImprimeMatriz(Coef , m, m);
  // printf("%d linhas iguais\n",CompareMatriz(Coef, Prod,m, m));
  
  // v = SubstituicaoDireta(L, m, b);   
  // v = SubstituicaoReversa(U, m, v);
  // printf("Raizes = "); 
  // ImprimeVetor(v, m);

  // puts("\n Testes =");
  // v = MatrizxVetor(Prod, m, m, v);
  // ImprimeVetor(v, m);

  return 0;
}