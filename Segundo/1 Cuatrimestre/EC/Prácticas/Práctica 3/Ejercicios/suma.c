#include<stdlib.h>	// Para exit()
#include<stdio.h>	// para printf()

int lista[]={1,2,10, 1,2,0b10, 1,2,0x10};
int longlista=sizeof(lista)/sizeof(int);
int resultado = 0;

int suma(int *array, int len){
	int res = 0;
	for(int i=0; i<len; ++i)
		res+=array[i];
	return res;
}

int main(){
	resultado=suma(lista,longlista);
	printf("resultado = %d = %0x hex\n", resultado, resultado);
	exit(0);
}