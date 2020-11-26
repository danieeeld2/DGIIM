#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>

int main(int argc, char *argv[]){
	pid_t pid;
	char *argumentos[argc];
	bool bg = false;

	if(argc < 2){
		perror("Error en los argumentos\n");
		exit(-1);
	}

	int contador=0; 
	for (int i=1; i<argc; i++){
		if(strcmp(argv[i], "bg") == 0){	// Compara dos strings
			bg = true;	// Opción de ejecutar eb segundo plano
		}
		else{
			// Concatenamos todos los argumentos
			argumentos[contador] = (char*) malloc(strlen(argv[i])+1);
			strcpy(argumentos[contador], argv[i]);
			contador++;
		}
	}

	int tam = contador;
	argumentos[contador] = NULL;

	if(bg){	// Se ejecuta en background
		if((pid = fork()) < 0){
			perror("Error, creación errónea de los hijos\n");
			exit(-1);
		}
		else if(pid == 0){	// Hacemos que lo ejecute el hijo, para que así se haga en backgroung
			if(execvp(argv[1], argumentos) < 0){
				perror("Error en execvp\n");
				exit(-1);
			}
		}
	}
	else{
		if(execvp(argv[1], argumentos) < 0){	// Lo ejecuta el padre en foregroung
			perror("Error en execvp\n");
			exit(-1);
		}
	}

	for(int i=0; i<tam; i++){
		free(argumentos[i]);
	}
	
	return(EXIT_SUCCESS);
}