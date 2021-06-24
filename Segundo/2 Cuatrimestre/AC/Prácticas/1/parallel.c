#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num()    0
#endif

int main(int argc, char **argv)  {
   int thread;
   if(argc < 2)     {
       fprintf(stderr,"\nFalta nº de thread \n");
       exit(-1);
   }
   thread = atoi(argv[1]);
#pragma omp parallel 
   {
      if ( omp_get_thread_num() < thread ) 
         printf("  thread %d realiza la tarea 1\n",
               omp_get_thread_num());
      else 
         printf("  thread %d realiza la tarea 2\n",
               omp_get_thread_num());
   }
   return(0);
}
