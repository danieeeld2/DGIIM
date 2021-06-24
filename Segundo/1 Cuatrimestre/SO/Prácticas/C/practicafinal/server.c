#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <signal.h>

#define tamano 1024
#define longnombre 50
#define MAX_CLIENTS 100

static void signal_handler(int sigNum){
    pid_t pid;
    char fifoproxy[longnombre];

    // Capturar pid del hijo y eliminar su archivo fifo asociado.
    pid = wait(NULL);
}

int main(int argc, char *argv[]){
    int fde, fds, fdc, tmp_cli;
    char nombrefifoe[longnombre];
    char nombrefifos[longnombre];
    char fifoproxy[longnombre];
    int leidos, proxypid;
    pid_t pid;

    //Comprobar el uso correcto del programa
    if(argc != 2) {
        printf("Uso: Servidor <nombre_fifo>");
        exit(-1);
    }

    // Manejador de señal SIGCHLD.
    signal(SIGCHLD, signal_handler);

    // Componer nombre del archivo fifo
    sprintf(nombrefifos,"%ss",argv[1]);
    sprintf(nombrefifoe,"%se",argv[1]);

    // Crear archivos fifo
    umask(0);  
    mkfifo(nombrefifoe,0666);   
    mkfifo(nombrefifos,0666);

    //Intentar abrir los archivos fifo.
    if((fds=open(nombrefifos,O_RDWR)) < 0){
        perror("\nNo se pudo abrir el archivo fifo del servidor.");
        exit(-1);
    }

    if((fde=open(nombrefifoe,O_RDWR)) < 0){
        perror("\nNo se pudo abrir el archivo fifo del cliente.");
        exit(-1);
    }

    // Creación del archivo bloqueo que se utilizará como cerrojo.
    umask(0);
    if((fdc=open("blockfile", O_CREAT, 0666))<0){
        printf("\nError al crear el archivo de bloqueo.");
        exit(-1);
    }

    // Lanzar procesos mientras se reciba algo del archivo fifo cliente.
    while((leidos=read(fde, &tmp_cli, sizeof(int))) != 0){
        pid = fork();
        if (pid == 0){ //Proceso hijo.
            // Obtener pid del nuevo proceso
            proxypid = getpid();
            // Construir cadena "proxy.getpid()" para archivo fifo.
            sprintf(fifoproxy,"fifo.%d", proxypid); 
            // Crear archivo fifo.
            umask(0);
            mkfifo(fifoproxy,0666);
            // Escribe el pid del proxy en fifos
            write(fds, &proxypid, sizeof(int));
            // Abrir fifo para lectura.
            int fifo = open(fifoproxy,O_RDONLY);
            // Redirigir entrada standar -> archivofifo
            dup2(fifo, STDIN_FILENO);
            execlp("./proxy", "proxy", NULL);
            exit(0);
        }
    }

    return 0;
} 