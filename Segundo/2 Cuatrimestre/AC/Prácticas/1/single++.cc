#include <omp.h>
#include <iostream>
#include <iterator>
#include <valarray>

template<class T> 
std::ostream& operator<<(std::ostream& os, const std::valarray<T>& v)
{
	std::copy(std::begin(v), std::end(v), std::ostream_iterator<T>(os, " "));
	return os;
}

int main()
{
	int a, n = 9;
	std::valarray<int> b(n);

	b = -1;

	std::cout << "antes de la región paralela: b = < " 
	          << b << ">" << std::endl;

	#pragma omp parallel 
	{
		#pragma omp single
		{
			std::cout << "introduce el valor de inicialización de a: ";
			std::cin >> a;
			std::cout << "cláusula single ejecutada por " 
			          << omp_get_thread_num() << std::endl;
		}

		#pragma omp for
		for (auto& i: b)
			i = a;
	}

	std::cout << "después de la región paralela: b = < " 
	          << b << ">" << std::endl;
}
