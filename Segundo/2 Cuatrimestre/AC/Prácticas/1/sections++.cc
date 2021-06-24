#include <omp.h>
#include <iostream>

void fa()
{
	std::cout << "fa() ejecutada por " +
	             std::to_string(omp_get_thread_num()) + "\n";
}

void fb()
{
	std::cout << "fb() ejecutada por " +
	             std::to_string(omp_get_thread_num()) + "\n";
}

int main()
{
	#pragma omp parallel sections
	{
		#pragma omp section
		fa();
		#pragma omp section
		fb();
	}
}
