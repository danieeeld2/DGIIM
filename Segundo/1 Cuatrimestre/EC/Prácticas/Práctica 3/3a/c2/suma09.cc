//------------------------------------------------------------------------------
// suma_09.cc
//------------------------------------------------------------------------------

#include <algorithm> // max_element min_element
#include <chrono>    // duration_cast high_resolution_clock microseconds
#include <iomanip>   // setw
#include <iostream>  // cout endl
#include <numeric>   // accumulate iota

//------------------------------------------------------------------------------

const int N = 1 << 16, REP = 9999;

int lista[N];

//------------------------------------------------------------------------------

int suma1(int* array, int len)
{
	int res = 0;
	for (int i = 0; i < len; i++)
		res += array[i];
	return res;
}

//------------------------------------------------------------------------------

int suma2(int* array, int len) // no funciona si len == 0
{
	asm("    xor %eax, %eax           # resultado = 0   \n"
	    "    xor %edx, %edx           # i = 0           \n"
	    "1:  add (%rdi,%rdx,4), %eax  # res += array[i] \n"
	    "    inc %edx                 # ++i             \n"
	    "    cmp %edx,%esi            # i < len?        \n"
	    "    jne 1b                   # repetir?        \n"
	    "    ret                      # why? -O3        \n"
	);
}

//------------------------------------------------------------------------------

int suma3(int* array, int len) // funciona aunque len == 0
{
	asm("    xor %eax, %eax           # resultado = 0   \n"
	    "    xor %edx, %edx           # i = 0           \n"
	    "1:  cmp %edx, %esi           # i < len?        \n"
	    "    je 2f                    # acabar?         \n"
	    "    add (%rdi,%rdx,4), %eax  # res += array[i] \n"
	    "    inc %edx                 # ++i             \n"
	    "    jmp 1b                   # repetir         \n"
	    "2:  ret                      # why? -O3        \n"
	);
}

//------------------------------------------------------------------------------

int suma4(int* array, int len)
{
	int res = 0;
	asm("    xor %%edx, %%edx        # i = 0           \n"
	    "1:  cmp %%edx, %%esi        # i < len?        \n"
	    "    je 2f                   # acabar?         \n"
	    "    add (%%rdi,%%rdx,4), %0 # res += array[i] \n"
	    "    inc %%edx               # ++i             \n"
	    "    jmp 1b                  # repetir         \n"
	    "2:                                            \n"
	    :"+r" (res));
	return res;
}

//------------------------------------------------------------------------------

int suma5(int* array, int len)
{
	int res = 0;
	for (long long i = 0; i < len; ++i)
	asm("add (%[a],%[i],4),%[r] \n" // code
	     : [r] "+r" (res)           // output-input
	     : [i] "r"  (i),            // input // also ((long long)i)
	       [a] "r"  (array)         // clobber
	   );
	return res;
}

//------------------------------------------------------------------------------

int suma6(int* array, int len)
{
	int res = 0;
	for (long long i = 0; i < len; ++i)
	asm("add (%2,%1,4),%0 \n" : "+r"(res) : "r"(i), "r"(array));
	return res;
}

//------------------------------------------------------------------------------

int suma7(int* array, int len)
{
	int res = 0;
	int *end = array + len;
	while(array != end)
		res += *array++;
	return res;
}

//------------------------------------------------------------------------------

int suma8(int* array, int len)
{
	return std::accumulate(array, array + len, 0);
}

//------------------------------------------------------------------------------

template <class F> void test(F& f, const char* msg)
{
	using namespace std::chrono;

	double t[REP];
	int resultado = 0;

	for (auto& i: t)
	{
		auto start = high_resolution_clock::now();
		resultado = f(lista, N);
		auto stop  = high_resolution_clock::now();
		i = duration_cast<nanoseconds>(stop - start).count() / 1000.0;
	}

	std::nth_element(t, t + REP / 2, t + REP); // for median

	std::cout << std::setw(28) << msg
	          << std::setw(15) << resultado
	          << std::setw(8) << std::fixed << std::setprecision(2)
	          << *std::min_element(t, t + REP) << "us"
	          << std::setw(10) << std::fixed << std::setprecision(2)
	          << t[REP / 2] << "us"
	          << std::setw(8) << std::fixed << std::setprecision(2)
	          << *std::max_element(t, t + REP) << "us"
	          << std::endl;
}

//------------------------------------------------------------------------------

int main()
{
	std::iota(lista, lista + N, 0);

	std::cout << std::setw(28) << "version"
	          << std::setw(15) << "resultado"
	          << std::setw(10) << "min"
	          << std::setw(12) << "median"
	          << std::setw(10) << "max" << std::endl
	          << std::string(75, '-') << std::endl;

	test(suma1, "suma1 (C for           )");
	test(suma2, "suma2 (asm basico      )");
	test(suma3, "suma3 (asm basico v2   )");
	test(suma4, "suma4 (asm basico v3   )");
	test(suma5, "suma5 (asm extendido   )");
	test(suma6, "suma6 (asm extendido v2)");
	test(suma7, "suma7 (C while         )");
	test(suma8, "suma8 (std::accumulate )");
}

//------------------------------------------------------------------------------
