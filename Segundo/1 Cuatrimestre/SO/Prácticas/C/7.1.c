#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd, i;
    char * argumentos[argc];
    char * sym = argv[argc-2];
    char * filename = argv[argc-1];
    for(i=0; i<argc-3; i++){
        argumentos[i] = (char*) malloc(strlen(argv[i+1])+1);
        strcpy(argumentos[i],argv[i+1]);
    }
    argumentos[i] = NULL;

    if(argc < 2){
        printf("Error en el número de argumentos\n");
        exit(EXIT_FAILURE);
    }

    if(strcmp(sym, ">") == 0){
        // Abrimos el archivo para escritura
        if((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC , S_IRWXU)) < 0){ // Comprobamos si falla la apertura
            printf("Error en el open\n");
            exit(EXIT_FAILURE);
        }
        close(STDOUT_FILENO); // Cerramos la salida estándar

        //  Ajustamos las banderas del archivo abierto fd
        /*  F_DUPFD duplica el descriptor de archivo especificado en fd.
            El tercer argumento (STDOUT_FILENO) especifica que el descriptor
            duplicado debe ser mayor o igual a dicho valor entero*/
        if(fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1){    // Comprobación de errores
            printf("Error en fcntl\n");
            exit(EXIT_FAILURE);
        }

        // Ejecutamos la orden
        if(execvp(argv[1], argumentos) < 0){
            printf("Error en execvp\n");
            exit(EXIT_FAILURE);
        }

    }else if(strcmp(sym, "<") == 0){ // Mismo poceso pero con redireccion de netrada
        if((fd = open(filename, O_RDONLY )) < 0){
            printf("Error en el open\n");
            exit(EXIT_FAILURE);
        }
        close(STDIN_FILENO);    // Cerramos la entrada estándar

        //  Ajustamos las banderas del archivo abierto fd
        /*  F_DUPFD duplica el descriptor de archivo especificado en fd.
            El tercer argumento (STDOUT_FILENO) especifica que el descriptor
            duplicado debe ser mayor o igual a dicho valor entero*/
        if(fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1){    // Comprobación de errores
            printf("Error en fcntl\n");
            exit(EXIT_FAILURE);
        }

        // Ejecutamos la orden
        if(execvp(argv[1], argumentos) < 0){
            printf("Error en execvp\n");
            exit(EXIT_FAILURE);
        }

    }else{
        printf("Error, el probrama debe usarse como: ./programa <orden> \">\"|\"<\" <archivo\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}