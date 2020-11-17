int suma(int *begin, int *end)
{
	int r = 0;
	while (begin != end)
		r += *begin++;
	return r;
}
