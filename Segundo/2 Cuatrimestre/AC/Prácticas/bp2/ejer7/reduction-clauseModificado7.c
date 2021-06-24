/**
 * @file reduction-clauseModificado7.c
 * @author Daniel Alconchel Vázquez
 */

#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv) {
    int i, n=20, a[n],suma=0;

    if(argc < 2){ fprintf(stderr,"Falta iteraciones\n"); exit(-1);}

    n = atoi(argv[1]);

    if (n>20){ n=20; printf("n=%d",n); }

    for (i=0; i<n; i++)
        a[i] = i;

    #pragma omp parallel
    {
      int suma_parallel = 0;

      #pragma omp for
      for(int i=0; i<n; i++)
        suma_parallel += a[i];

      #pragma omp atomic
        suma += suma_parallel;
    }

    printf("Tras 'parallel' suma=%d\n",suma);
}
