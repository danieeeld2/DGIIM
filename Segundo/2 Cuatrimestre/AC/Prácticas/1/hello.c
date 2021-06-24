#include <stdio.h>

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

int main() { 
 int ID;
 #pragma omp parallel private(ID) 
 {
   ID = omp_get_thread_num();
   printf("Hello(%d)",ID);
   printf("World(%d)\n",ID);
 }
 return 0;
}
