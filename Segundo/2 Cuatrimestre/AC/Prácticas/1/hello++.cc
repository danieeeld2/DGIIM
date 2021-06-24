#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num() 0
#endif

#include <iostream>
#include <string>

int main()
{
	#pragma omp parallel
	{
		std::string id = std::to_string(omp_get_thread_num());
		std::cout << "Hello(" + id + ")"
		          << "World(" + id + ")\n";
	}
}
