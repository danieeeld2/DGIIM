int suma(int *lista, int n)
{
	int resultado = 0;
	for (int i = 0; i < n; ++i)
		resultado += lista[i];
	return resultado;
}
