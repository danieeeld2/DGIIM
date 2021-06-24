/**
 * @file shared-clause.c
 * @author Daniel Alconchel Vázquez
 */

#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#endif

int main()
{
    int i, n = 7;
    int a[n];

    for (i=0; i<n; i++)
        a[i] = i+1;

    #pragma omp parallel for shared(a)
        for (i=0; i<n; i++) a[i] += i;

    printf("Despues de parallel for:\n");
    for (i=0; i<n; i++)
        printf("a[%d] = %d\n",i,a[i]);
}
