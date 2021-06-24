#include <omp.h>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono;

int main()
{
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		if (id < omp_get_num_threads() / 2)
			std::this_thread::sleep_for(3s);

		auto before = steady_clock::now();

		#pragma omp barrier

		auto s = duration_cast<seconds>(steady_clock::now() - before);

		std::cout << "la hebra " + std::to_string(id) +
		             " espera en la barrera durante " + 
		             std::to_string(s.count()) + "s\n";
	}
}
