#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//#define GLOBAL
#define DYN

#ifdef GLOBAL
#define MAX 2000
int matriz[MAX][MAX];
int v1[MAX];
int v2[MAX];
#endif

int main(int nargs, char **vargs) {
  if (nargs < 2) {
    printf("Error, uso programa: %s <dimensiones>", vargs[0]);
    exit(1);
  }

  int n = atoi(vargs[1]);
  int j;
  unsigned seed;
#ifdef DYN
  int **matriz = malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
    matriz[i] = malloc(n * sizeof(int));
  int *v1 = malloc(n * sizeof(int));
  int *v2 = malloc(n * sizeof(int));
#endif

  // Inicializacion
#pragma omp parallel for private(j, seed)
  for (int i = 0; i < n; i++) {
    seed = 25234 + 17 * omp_get_thread_num();
    v1[i] = rand();
    for (j = 0; j < n; j++)
      matriz[i][j] = rand_r(&seed);
  }
  double t1 = omp_get_wtime();
  // Producto
#pragma omp parallel for private(j)
  for (int i = 0; i < n; i++) {
    v2[i] = 0;
    for (j = 0; j < n; j++) {
      v2[i] += matriz[i][j] * v1[j];
    }
  }

  double t2 = omp_get_wtime();

  printf("%d - %d\n", v2[0], v2[n - 1]);
  printf("time: %f\n", t2 - t1);

#ifdef DYN
  for (int i = 0; i < n; i++)
    free(matriz[i]);
  free(matriz);
  free(v1);
  free(v2);
#endif
}
