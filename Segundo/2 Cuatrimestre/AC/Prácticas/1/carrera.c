#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)   {
   int i, n=20, a[n],suma=0;
   if(argc < 2)   {
       fprintf(stderr,"\nFalta iteraciones\n"); exit(-1);
   } 
   n = atoi(argv[1]); 
   if (n>20) n=20; 
   for (i=0; i<n; i++)
       a[i] = i+1; 
 
#pragma omp parallel for  
   for (i=0; i<n; i++)
      suma = suma + a[i];

   printf("Fuera de 'parallel' suma=%d\n",suma); 
   return(0);
}
