#include <iostream>

// 4294967295 + 4294967295 = 8589934590
// 0xffffffff + 0xffffffff = 0x1fffffffe

unsigned lista[] = {0xffffffff, 0xffffffff};
unsigned n = sizeof(lista) / sizeof(unsigned);

unsigned suma1(unsigned *lista, unsigned longlista)
{
	unsigned total = 0;
	for (unsigned i = 0; i < longlista; ++i)
		total += lista[i];
	return total;
}

unsigned suma2(unsigned *begin, unsigned *end)
{
	unsigned total = 0;
	while (begin != end)
		total += *begin++;
	return total;
}

int main()
{
	unsigned s1 = suma1(lista, n),
	         s2 = suma2(lista, lista + n);
	
	std::cout << "suma1 = " << std::dec << s1 
	          << " / 0x" << std::hex << s1 << std::endl
	          << "suma2 = " << std::dec << s2 
	          << " / 0x" << std::hex << s2 << std::endl;
}
