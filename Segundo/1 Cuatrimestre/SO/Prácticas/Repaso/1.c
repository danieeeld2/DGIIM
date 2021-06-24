#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv){
    int fdout, fdin;
    int leidos = 0;
    char buffer[80];
    char block[20];
    int i=0;
    

    if(argc == 2){
        if((fdin=open(argv[1],O_RDONLY)) < 0){
            //printf("Error al abrir el archivo", errno);
            //perror("Error al abrir el archivo");
            //exit(-1);
        }
    }else{
        fdin=STDIN_FILENO;
    }

    if((fdout=open("salida.txt", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR)) < 0){
        printf("Error al abrir el archivo", errno);
        perror("Error al abrir el archivo");
        exit(-1);
    }

    while((leidos=read(fdin,buffer,80)) != 0){
        i++;
        sprintf(block, "\nBloque %d\n", i);
        write(fdout, block, strlen(block));
        write(fdout, buffer, 80);
    }

    if(close(fdin) == -1){
        printf("Error %d en close\n", errno);
        perror("Error en close\n");
        exit(-1);
    }

    if(close(fdout) == -1){
        printf("Error %d en close\n", errno);
        perror("Error en close\n");
        exit(-1);
    }

    return 0;
}