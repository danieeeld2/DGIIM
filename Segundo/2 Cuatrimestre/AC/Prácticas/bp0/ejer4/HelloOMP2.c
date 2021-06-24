/* Compilar con:
 * gcc -O2 -fopenmp -o HelloOMP HelloOMP.c
 */
#include <stdio.h>
#include <omp.h>

int main(void){
	#pragma omp parallel
	printf("(%d:!!!Hello...)\n",
		omp_get_thread_num());
	printf("(%d:...World!)\n",
		omp_get_thread_num());
	return(0);
}
