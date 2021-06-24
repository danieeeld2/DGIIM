#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char **argv)   {
   int i, n=20, a[n],suma=0,sumalocal;
   if(argc < 2)     {
         fprintf(stderr,"\nFalta iteraciones\n"); exit(-1);
   } 
   n = atoi(argv[1]); if (n>20) n=20; 

   for (i=0; i<n; i++)    a[i] = i; 
 
#pragma omp parallel private(sumalocal)
{  sumalocal=0;
   #pragma omp for  schedule(static)
   for (i=0; i<n; i++)
   {   sumalocal += a[i];
       printf(" thread %d suma de a[%d]=%d sumalocal=%d \n",  omp_get_thread_num(),i,a[i],sumalocal);
   } 
   #pragma omp critical 
       suma = suma + sumalocal;
}  
   printf("Fuera de 'parallel' suma=%d\n",suma);
   return(0);
}
