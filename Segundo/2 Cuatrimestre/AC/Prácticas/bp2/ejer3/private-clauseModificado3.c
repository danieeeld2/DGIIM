/**
 * @file private-clauseModificado3.c
 * @author Daniel Alconchel vázquez
 */

#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main()
{
    int i, n = 7;
    int a[n], suma;
    for (i=0; i<n; i++)
        a[i] = i;

    //ELIMINACION DE private(suma)
    #pragma omp parallel
    {
        suma=0;
        #pragma omp for
        for (i=0; i<n; i++)
        {
            suma = suma + a[i];
            printf("thread %d suma a[%d] / ", omp_get_thread_num(), i);
        }

        printf("\n* thread %d suma= %d", omp_get_thread_num(), suma);
    }

    printf("\n >> [THREAD : %d] | FUERA DE PARALLEL --> SUMA = %d",omp_get_thread_num(),suma);

    printf("\n");
}
