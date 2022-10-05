#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double *LerVetor(char *nome, int *m) {
  FILE *fp = fopen(nome, "r");
  double *v;
  int i; 

  fscanf(fp, "%d",m);
  v = malloc((*m)*sizeof(double));
  for(i=0; i<*m; i++) {
    fscanf(fp,"%lf",&v[i]); 
  }
  return v;
}

double norma(double *v, int m, double p) {
  double n=0;
  int i;
  
  if (p==0) {
    n = fabs(v[0]);
    for (i=1; i<m; i++) {
      if (fabs(v[i])>n) n=fabs(v[i]);
    }
  } 
  else {
    for (i=0; i<m; i++) {
      n+=pow(fabs(v[i]),p);
    }
    n = pow( n, 1./p);
  }   
  return n;
}

int main(int argc, char **argv) {
    double *V;
    int m, i;

    V = LerVetor(argv[1],&m);
    for(i=0; i<m; i++) 
      printf("%lf ", V[i]);
    printf ("\n\nNorma=%lf\n", norma(V,m,0));
    return 0;
}
