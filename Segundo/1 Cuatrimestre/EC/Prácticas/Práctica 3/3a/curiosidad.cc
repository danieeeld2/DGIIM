#include <functional>
#include <random>

int suma1(int* begin, int *end)
{
	int total = 0;
	asm("0: cmp %0,%2     \n"
		"   je 1f         \n"
		"   add $4,%0     \n" // esto se
		"   add -4(%0),%1 \n" // ve raro
		"   jmp 0b        \n"
		"1:               \n"
		:"+r"(begin), "+r"(total)
		:"r"(end));
	return total;
}

int suma2(int* begin, int *end)
{
	int total = 0;
	asm("0: cmp %0,%2     \n"
		"   je 1f         \n"
		"   add (%0),%1   \n" // ahora no,
		"   add $4,%0     \n" // verdad?
		"   jmp 0b        \n"
		"1:               \n"
		:"+r"(begin), "+r"(total)
		:"r"(end));
	return total;
}

int main()
{
	const int N = 1000000, R = 100;
	int lista[N], resultado = 0;
	std::random_device device;
	std::mt19937 generator(device());
	std::bernoulli_distribution distribution;
	auto _5050 = std::bind(distribution, generator);
	
	for (int i = 0; i < N; ++i)
		lista[i] = i;
	
	for (int i = 0; i < R; ++i)
		if (_5050())
			resultado ^= suma1(lista, lista + N) + suma2(lista, lista + N);
		else
			resultado ^= suma2(lista, lista + N) + suma1(lista, lista + N);
	
	return resultado;
}
