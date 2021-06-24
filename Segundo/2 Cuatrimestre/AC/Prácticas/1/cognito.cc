// cognito.cc

#ifndef _OPENMP
#include <omp.h>
#else
#define omp_set_num_threads(x)
#endif

#include <iostream>

int main()
{
	omp_set_num_threads(100);
	#pragma omp parallel
	std::cout << "cognito, ergo sum!" << std::endl;
}
