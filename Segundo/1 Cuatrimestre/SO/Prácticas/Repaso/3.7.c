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
    bool bg = false;
    char *argumentos[argc];
    int contador = 0;

    if(argc < 2){
        printf("El programa se ejecuta como: ./script <orden> <param1> ... <paramn> [<bg>]\n", errno);
        perror("Error en los argumentos\n");
        exit(-1);
    }

    for(int i=1; i < argc; i++){
        if(strcmp(argv[i], "bg") == 0){
            bg = true;
        }else{
            argumentos[contador] = (char*) malloc(strlen(argv[i])+1);
            strcpy(argumentos[contador], argv[i]);
            contador++;
        }
    }
    argumentos[contador] = NULL;
    int tam=contador;

    if(!bg){    // Lo ejecuta el padre
        if((execvp(argv[1], argumentos)) < 0){
                printf("Error en la ejecución\n", errno);
                perror("execvp");
                exit(-1);
            }
    }else{  // Se ejecuta en background y hacemos que lo ejecute el hijo
        if((pid = fork()) < 0){
            printf("Error al crear el hijo\n", errno);
            perror("Error en fork");
            exit(-1);
        }
        if(pid == 0){
            if((execvp(argv[1], argumentos)) < 0){
                printf("Error en la ejecución\n", errno);
                perror("execvp");
                exit(-1);
            }
            exit(EXIT_SUCCESS);
        }
    }

    for(int i=1; i<tam; i++){
		free(argumentos[i]);
	}
	
	return(EXIT_SUCCESS);
}