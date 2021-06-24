#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

#define VAR_DYNAMIC 

int main(int argc, char **argv){
  struct timespec cgt1, cgt2;
  double ncgt;
  int k=0;

  if (argc < 2)
  {
    printf("FALTA LA NENSION");
    exit(-1);
  }

  int N = atoi(argv[1]);

  double **m1, **m2, **mm;

  m1 = (double **)malloc(N * sizeof(double *));
  m2 = (double **)malloc(N * sizeof(double *));
  mm = (double **)malloc(N * sizeof(double *));

  for (int i = 0; i < N; i++){
    m1[i] = (double *)malloc(N * sizeof(double));
    m2[i] = (double *)malloc(N * sizeof(double));
    mm[i] = (double *)malloc(N * sizeof(double));
  }

  double t_inicial, t_final;
  int i = 0, j = 0;

 
  for (i = 0; i < N; i++){
    for (j = 0; j < N; j++){
      m1[i][j] = drand48();
      m2[i][j] = drand48();
      mm[i][j] = 0;
    }
  }

  t_inicial = omp_get_wtime();

  #pragma omp parallel for private(j,k)
      for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
          for (int k = 0; k < N; k++)
            mm[i][j] += m1[i][k] * m2[k][j];

  
  t_final = omp_get_wtime();
  
  double t = t_final - t_inicial;

  printf("TIEMPO DE EJECUCION: %11.9f || DIMENSION: %d \n", t, N);

  for(int i=0; i<N; i++){
    free(m1[i]);
    free(m2[i]);
    free(mm[i]);
  }
  free(m2);free(m1);free(mm);

  return EXIT_SUCCESS;
}
