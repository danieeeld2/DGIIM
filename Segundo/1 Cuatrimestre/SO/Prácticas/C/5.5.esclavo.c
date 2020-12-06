#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int esPrimo(int num);

int main(int argc, char *argv[]){
	int min, max;
	int i;

	read(STDIN_FILENO, &min, sizeof(int));
	read(STDIN_FILENO, &max, sizeof(int));
	// Recordemos que con dup2 hemos hecho que el maestro escriba en
	// la entrada estándar

	for(i = min; i <= max; i++){
		if(esPrimo(i)){
			write(STDOUT_FILENO, &i, sizeof(int));
		}
	}

	return EXIT_SUCCESS;
}

int esPrimo(int num){
	int i;
	int bandera = 1;

	if(num == 0 || num == 1 || num == 4)
		return bandera;
	for(i=2; i<num/2; i++)
		if(num%i == 0)
			bandera = 0;

	return bandera;
}
