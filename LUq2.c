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

double **MatrizxMatriz(double **M1, int m1, int n1, double **M2, int p, int q){
  int i, j, k;
  double **M;

  if(n1!=p) 
    puts("Erro! Não foi possível multiplicar as raízes!");

  M = malloc(m1*sizeof(double *));
  for(i=0; i<m1; i++) M[i]=malloc(q*sizeof(double));

  for(i=0; i<m1; i++){
    for(j=0; j<q; j++){
      M[i][j]=0;
      for(k=0; k<p; k++) M[i][j] += M1[i][k]*M2[k][j];
    }
  }
  return M;
}

void **LUPivot(double **M, double ***L, double ***U, double **b, int m, int n ){
  int i, j, k, p;
  double lbd, pivot; 

  //Alocação de memória
  *L = calloc(m, sizeof(double *)); 
  for(i=0; i<m; i++) (*L)[i] = calloc(m, sizeof(double));

  *U = malloc(m* sizeof(double *));
  for(i=0; i<m; i++) (*U)[i] = malloc (m * sizeof(double));

  *b = malloc(m * sizeof(double));
  for(i=0; i<m; i++) (*b)[i] = M[i][n-1];

  //Inicialização
  for(i=0; i<m; i++){
    (*L)[i][i] = 1;
    for(j=0; j<m;j++){
      (*U)[i][j] = M[i][j];
    }
  }

  //Loop em colunas 
  for(j=0; j<m; j++){
    
    pivot = (*U)[j][j]; 
    p=0;

    for(i=j+1; i<m; i++){
      if(fabs((*U)[i][j])>pivot){
        pivot = fabs((*U)[i][j]);
        p = i;
      }
    }

    if(p){
      TrocaLinha(&(*U)[p], &(*U)[j]);
      lbd = (*b)[p];
      (*b)[p]=(*b)[j];
      (*b)[j] = lbd;
    }
  

    //Escalonamento 
    for(i=j+1; i<m; i++){
        lbd = (*L)[i][j] = (*U)[i][j] / (*U)[j][j];
      for(k=j; k<m; k++) 
        (*U)[i][k] -= lbd*(*U)[j][k];
    }
  }
}

double *SubstituicaoDireta(double **M, int m, double *b){
  double *y, sum;
  int i, j;

  y = malloc(m*sizeof(double));

  for(i=0; i<m; i++){
    sum = 0;
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
    sum = 0;
    for(j=i+1; j<=m-1; j++){
      sum += M[i][j]*y[j];
    }
    y[i] = (b[i]-sum)/M[i][i];
  }
  return y;
}

double *MatrizxVetor(double **M, int m, int n,double *x){
  int i, j, k;
  double *resultado;

  resultado = malloc(m*sizeof(double *));

  for(i=0; i<m; i++){
    for(j=0; j<n; j++){
      resultado[i]+=M[i][j]*x[j];
    }
  }
  return resultado;
}

//Auxilia na implementação da matriz inversa pela decomposição LU 
//com pivotamento
double **MatrizTransposta(double **Matriz, int nl, int nc){
  double **T;
  int i, j;

  T = (double **) malloc(nc *sizeof(double *));
  for (i=0; i<nc; i++){
      T[i] = (double *) malloc(nl *sizeof(double));
  }

  for(i=0; i<nc; i++){
    for (j=0; j<nl; j++){
      T[i][j]=Matriz[j][i];
    }
     puts("");
  }
  return T;
}

//Função solicitada na função main
void SeparaSistema(double **M, int nl, int nc, double ***K, double **x){
  int i; 

  *K = malloc(nl*sizeof(double *));
  for(i=0; i<nl; i++) (*K)[i] = malloc(nl*sizeof(double));

  *x = malloc(nl*sizeof(double *));
  
  for(i=0; i<nl; i++){
    memcpy((*K)[i], M[i], nl*sizeof(double));
    (*x)[i] = M[i][nc-1];
  }
}

double **Inversa(double **C, int nl, int nc, double **b){
  
  int i;
  double **K, **L, **U, **x, **y;
  K = calloc(nl, sizeof(double *));
  for(i=0; i<nl; i++) K[i] = calloc(nl, sizeof(double));

  y = malloc(nl*sizeof(double *));
  for(i=0; i<nl; i++) y[i] = malloc(nl*sizeof(double));
  x = malloc(nl*sizeof(double *));
  for(i=0; i<nl; i++) x[i] = malloc(nl*sizeof(double));

  for(i=0; i<nl; i++){
    K[i][i] = 1;
  }
  
  LUPivot(C, &L, &U, b, nl, nc);

  for(i=0;i<nl;i++){
    y[i]=SubstituicaoDireta(L,nl,K[i]);
    x[i]=SubstituicaoReversa(U,nl,y[i]);
  }
  
  return MatrizTransposta(x,nl,nl);
}

void ImprimeVetor(double *v, int j){
  int i;
  for(i=0; i<j; i++) printf("x[%d] = %g\n", i, v[i]);
}

int main(int argc, char **argv) {
  int m, n;
  double **M, **W, **C, **L, **U, *b, *raizes;

  M=LeMatriz(argv[1], &m, &n);
  SeparaSistema(M,m,n,&C,&b);
  
  /*
  Cálculo da Inversa usando a decomposição LU
  com pivoteamento
 */
  
  W = Inversa(M, m, n, &b);
  raizes = MatrizxVetor(W,m,m,b);
  ImprimeVetor(raizes,m);

  /*  
    Esse programa calcula a matriz inversa (da matriz dos coeficientes - quadrada) por meio da decomposição LU. Para isso, fazemos a separação do sistema original, isto é, separamos a chamada matriz dos coeficientes e a chamada matriz dos termos independentes. Além disso, o programa encontra as soluções (raízes) do sistema linear. Isso pode ser observado com o uso da função MatrizxVetor, que multiplica a matriz inversa pela matriz coluna dos termos independentes do sistema. Finalmente, com a função ImprimeVetor, as soluções são impressas e, logo em seguida, o programa é finalizado.
 */

  return 0;
}