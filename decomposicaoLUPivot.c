#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double **LeMatrix (char *nome, int *m, int *n)  {  
  FILE *fp = fopen(nome, "r"); 
  double **Matriz;
  int i, j, f;

  f = fscanf(fp, "%d %d", m, n);
  Matriz = (double **) malloc( *m* sizeof(double *) );
  for (i = 0; i<*m; i++)  Matriz[i] = malloc (*n * sizeof (double));

  for (i = 0; i<*m; i++) {
    for (j = 0; j<*n; j++) f = fscanf(fp,"%lf", &Matriz[i][j]);
  }
  return Matriz;
}

void ImprimeMatriz (double **M, int m, int n) {
  int i, j;

  for (i = 0; i < m; i++) {
    printf("| ");
    for (j = 0; j < n; j++) printf ("%9.5lf ", M[i][j]);
	  puts (" |");
  }
} 

void ImprimeVetor (double *V, int m) {
  int i;
   
  printf("( "); 
  for (i = 0; i < m; i++) printf ("%6.4g ", V[i]);https://www.gazetadopovo.com.br/vida-publica/fiquei-feliz-de-a-dilma-ter-sido-eleita-diz-romario-em-visita-a-camara-0a94kx1rsh1g3pxgn4a1rroem/
	puts (")");
} 

void TrocaLinhas (double **k, double **l) { 
  double *temp;
 
  temp = *k;
  *k = *l;
  *l = temp;
}

void LUPivot(double **M, double ***L, double ***U, double **b, int m, int n) {
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
      TrocaLinhas(&(*L)[p], &(*L)[j]); 
      lbd   = (*b)[p];
      (*b)[p] = (*b)[j];
      (*b)[j] = lbd; 
    }

/*  Escalonamento 
*/  
    for (i = j + 1; i < m; i++) {
      lbd =  (*U)[i][j] / (*U)[j][j];
      for(k=j; k<m; k++) (*U)[i][k] -= lbd*(*U)[j][k];
      (*L)[i][j] = lbd;
    } 
  }
  for (i=0; i<m; i++) (*L)[i][i] = 1;
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
  int i, j;
  double **Inv, **L, **U, *v, *b;

  Inv = calloc (m, sizeof (double *));
  for (i = 0; i < m; i++)  Inv[i] = calloc (m, sizeof (double ));
  v = calloc(m, sizeof(double)); 
  b = calloc(m, sizeof(double)); 
  LUPivot(A, &L, &U, &b, m, m);

  for (i = 0; i < m; i++) {
    v[i] = 1;
    b = SubstituicaoDireta(L, m, v); 
    b = SubstituicaoReversa(U, m, b);
    for(j = 0; j < m; j++) Inv[j][i] = b[j];
    v[i]=0;   
  }
  return Inv;  
}

int main (int argc, char **argv) {
  int m, n, i, j;
  double **M, **L, **U, **Coef, **Prod, **Inv,  *b, *v;


  if (argc) M = LeMatrix (argv[1], &m, &n);

  SeparaSistema(M, m, n, &Coef, &b);    
  puts(" A  = ");
  ImprimeMatriz(Coef, m, m);  

  puts("b=");
  ImprimeVetor(b, m); 

  LUPivot(M, &L, &U, &b,  m, n);
  puts("\n L = ");
  ImprimeMatriz(L, m, m);  
  puts("\n U = ");
  ImprimeMatriz(U, m, m);  

  Inv = MatrizxMatriz(L, m, m, U, m, m);
  // Inv = InversaMatriz(Coef, m);
  puts("\n LU = ");
  ImprimeMatriz(Inv, m, m);  

  b = SubstituicaoDireta(L, m, b);
  b = SubstituicaoReversa(U, m, b);

  puts("raizes =");
  ImprimeVetor(b, m);    

  return 0;
}
