#include <omp.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#if GCC_VERSION < 4080000
#include <ext/numeric>
#else
#include <algorithm>
#endif

int main(int argc, char *argv[])
{
	if (argc != 2)
		throw std::invalid_argument("necesito el número de iteraciones");

	int n;
	std::istringstream iss(argv[1]);
	iss >> n;
	if(!iss) 
		throw std::invalid_argument("número de iteraciones no válido");

	if (n > 20)
		n = 20;

	int a[n], suma = 0;

	std::iota(a, a + n, 0);

	#pragma omp parallel
	{
		int sumalocal = 0;

		#pragma omp for schedule(static)
		for (int i = 0; i < n; ++i)
		{
			sumalocal += a[i];

			#pragma omp critical
			std::cout << "hebra " << omp_get_thread_num() 
			          << ": suma de a[" << i << "] = " << a[i] 
			          << " sumalocal = " << sumalocal << std::endl;
		}

		#pragma omp atomic
		suma += sumalocal;

		#pragma omp barrier

		#pragma omp master
		std::cout << "en la hebra master = " << omp_get_thread_num() 
		          << " suma = " << suma << std::endl;
	}
}
