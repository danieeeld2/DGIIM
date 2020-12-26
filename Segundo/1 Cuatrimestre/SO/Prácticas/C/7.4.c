#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(){
    char blockfile[] = "/tmp/BlockFile";
    struct flock cerrojo;
    int fd;

    umask(0);

    if((fd = open(blockfile, O_CREAT | O_WRONLY, S_IWUSR)) < 0){
        printf("Error en open\n");
        exit(EXIT_FAILURE);
    }

    cerrojo.l_type = F_WRLCK;   // Cerrojo de escritura
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0;

    if(fcntl(fd, F_SETLK, &cerrojo) == -1){
        if(errno & (EACCES | EAGAIN)){
            printf("Ya se  está ejecutando otra instrucción de este programa\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Soy la instancia del programa\n");
    sleep(10);

    return EXIT_SUCCESS;
}