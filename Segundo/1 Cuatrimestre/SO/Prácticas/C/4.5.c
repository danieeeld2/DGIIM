#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define NUMHIJOS 5

int main(int argc, char *argv[]){
	int i,j,k;
	int buffer[NUMHIJOS];
	pid_t pid;

	if(setvbuf(stdout, NULL, _IONBF, 0)){	// Desactivamos el buffer
		perror("\nError en setvbuf\n");
	}

	for(i=0; i<NUMHIJOS && pid!=0; i++){
		if((pid = fork()) < 0){	// Creamos los hijos
			perror("Error en el fork\n");
			exit(-1);
		}
		buffer[i] = pid;	// Almacenamos en cada posición el pid de cada hijo
	}

	if(pid==0){	// Proceso hijo
		printf("\nSoy el proceso hijo %d\n", getpid());
		exit(0);
	}
	else{	// Proceso padre
		// Con k=0 esperamos a los impares y con k=1 a los pares
		for(j=k=0; j<2; j++){
			for(; k<NUMHIJOS; k+=2){
				// pid = waitpid(buffer[k], &estado, NULL) Si lo hacemos asi en estado
				// se almacena la forma en la que finalizó el hijo

				pid = waitpid(buffer[k], NULL, NULL);

				/*	Wait espera a cualquier hijo que cumpla la condición de estado. Por otro lado,
					waitpid hace lo mismo, pero espera concretamente al hijo con
					pid indicado en el primer argumento
				*/

				i--;
				// printf("\nAcaba de finalizar mi hijo con PID %d y con estado %d\n", pid, estado);
				printf("Acaba de finalizar mi hijo con PID %d\n", pid);
				printf("Solo me quedan %d hijos vivos\n", i);
			}
			k = 1;
		}
	}

	exit(EXIT_SUCCESS);
}