/**
 * @file scheduled-clauseModificado5.c
 * @author Daniel Alconchel Vázquez
 * @brief Modificacion de scheduled-clause
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
    int i, n=200, chunk, a[n], suma=0;

    if(argc < 3)
    {
        fprintf(stderr,"\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n>200)
        n=200;

    chunk = atoi(argv[2]);

    for (i=0; i<n; i++)
        a[i] = i;

    omp_sched_t kind; int chunk_value;

    #pragma omp parallel for firstprivate(suma) \
                lastprivate(suma) schedule(dynamic,chunk)
    for (i=0; i<n; i++)
    {
        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",
               omp_get_thread_num(),i,a[i],suma);

        //MODIFICACION EJERCICIO 5. MODIFICACION DE VARIABLES
        if(i == 3){
          //CAMBIAMOS DYN-VAR
          omp_set_dynamic(0);
          //CAMBIAMOS NTHREADS-VAR
          omp_set_num_threads(4);
          //CAMBIAMOS RUN-SCHED-VAR
          omp_set_schedule(1,2);
        }
        if(i == 0 || i == 3){
          if(i == 0){
            printf("MOSTRANDO VARIABLES ANTES DE MODIFICACION...\n");
          }
          else{
            printf("MOSTRANDO VARIABLES DESPUES DE MODIFICACION...\n");
          }
          //MOSTRANDO DENTRO DE PARALLEL LAS VARIABLES...
          omp_get_schedule(&kind, &chunk_value);
          printf("DENTRO DE OMP PARALLEL FOR: \n dyn-var: %d | nthreads-var: %d \
          thread-limit-var: %d, run-sched-var: %d, chunk: %d \n", \
          omp_get_dynamic(), omp_get_max_threads(), omp_get_thread_limit(), kind, chunk_value);
        }
    }

    printf("Fuera de 'parallel for' suma=%d\n",suma);
    //MOSTRANDO FUERA DE PARALLEL LAS VARIABLES...
    printf("FUERA DE OMP PARALLEL FOR: \n dyn-var: %d | nthreads-var: %d \
    thread-limit-var: %d, run-sched-var: %d, chunk: %d \n", \
    omp_get_dynamic(), omp_get_max_threads(), omp_get_thread_limit(), kind, chunk);

    return(EXIT_SUCCESS);
}
