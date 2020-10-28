#include <iostream>

//int lista[] = {-1, -1};                 // -1 = 0xffffffff
int lista[] = {2147483647, 2147483647}; // 2147483647 = 0x7fffffff
int n = sizeof(lista) / sizeof(int);

long long suma1(int *lista, int longlista)
{
	long long total = 0;
	for (int i = 0; i < longlista; ++i)
		total += lista[i];
	return total;
}

long long suma2(int *begin, int* end)
{
	long long total = 0;
	while (begin != end)
		total += *begin++;
	return total;
}

long long dividir(int *begin, int* end)
{
	return suma2(begin, end) / (end - begin);
}

int main()
{
	std::cout << "lista[" << n << "] = {";
	for (int i = 0; i < n; ++i)
		std::cout << lista[i] << ", ";
	std::cout << "\b\b}" << std::endl;

	long long s1 = suma1(lista, n),
	          s2 = suma2(lista, lista + n);
	
	std::cout << "suma1 = " << std::dec << s1 
	          << " / 0x" << std::hex << s1 << std::endl
	          << "suma2 = " << std::dec << s2 
	          << " / 0x" << std::hex << s2 << std::endl;

	std::cout << std::dec << s1 << " / " << n << " = " 
	          << dividir(lista, lista + n) << std::endl;
}
