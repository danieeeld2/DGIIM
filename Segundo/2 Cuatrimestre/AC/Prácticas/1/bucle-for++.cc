#include <omp.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

int main(int argc, char *argv[])
{
	if (argc != 2)
		throw std::invalid_argument("necesito el número de iteraciones");

	int max;
	std::istringstream iss(argv[1]);
	iss >> max;
	if(!iss) 
		throw std::invalid_argument("número de iteraciones no válido");

	#pragma omp parallel for
	for (int i = 0; i < max; ++i)
		std::cout << "la hebra " + std::to_string(omp_get_thread_num()) +
		             " ejecuta la iteración " + std::to_string(i) + "\n";
}
