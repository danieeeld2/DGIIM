#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[]){
    pid_t pid;
    int num;
    
    if(argc != 2){
        printf("El programa se ejecuta como: ./script <numero>\n", errno);
        perror("Error en los parámetros\n");
        exit(-1);
    }

    num = atoi(argv[1]);

    if((pid = fork()) < 0){
        printf("Error, no se ha podido ejecutar fork\n", errno);
        perror("Error en el fork");
        exit(-1);
    }

    if(pid == 0){   // Lo ejecuta el hijo
        if(num % 2 == 0){
            printf("El número %d es par\n", num);
        }else{
            printf("El número %d es impar\n", num);
        }
    }else{  // Lo ejecuta el padre
        if(num % 4 == 0){
            printf("El número %d es divisible entre 4\n", num);
        }else{
            printf("El número %d no es divisible entre 4\n", num);
        }
    }

    exit(EXIT_SUCCESS);
}