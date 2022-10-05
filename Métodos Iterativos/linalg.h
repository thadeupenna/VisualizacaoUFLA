#ifndef linalg_h__
#define linalg_h__

extern double  **mat_ler (int nl, int nc, char *nome);
extern void mat_imprime(double **M, int nl, int nc);
extern double **mat_transposta(double **M,int nl,int nc); 
extern double **mat_triangsup(double **M, int nl, int nc);

#endif  // linalg_h__