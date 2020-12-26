#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void UsoIncorrecto(){
    printf("La funciíon debe llamarse así: \"./ejercicio3.c <archivo>\"");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    if(argc!=2)
        UsoIncorrecto();
    
    struct flock cerrojo1, cerrojo2;
    int fd;
    pid_t pid;

    if((fd=open(argv[1], O_RDWR)) == -1){
        printf("Error en open");
        exit(EXIT_FAILURE);
    }

    cerrojo1.l_type = F_WRLCK;  // Cerrojo de escritura
    cerrojo1.l_whence = SEEK_SET;
    cerrojo1.l_start = 0;
    cerrojo1.l_len = 100;

    cerrojo2 = cerrojo1;
    cerrojo2.l_start = 300;

    // Padre
    if(fcntl(fd, F_SETLKW, &cerrojo1) == -1){
        // F_SETLKW establece un cerrojo sobre un archivo
        printf("\nPadre: Error cerrojo1\n");
        exit(EXIT_FAILURE);
    }
    printf("Padre: Cerrojo1 en el archivo\n");

    if((pid=fork()) < 0){
        printf("Error en el fork\n");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){   // Hijo
        if(fcntl(fd, F_SETLKW, &cerrojo2) == -1){
            printf("Hijo: Error en cerrjo2");
        }else{
            printf("HIjo: cerroj2 en el archivo\n");
        }

        sleep(1);   // El hijo bloqueará antes y el sistema operativo hará que el padre falle
        //sleep(3); // El hijo bloqueará después y el sistema operativo hará que el hijo falle

        if(fcntl(fd, F_SETLKW, &cerrojo1) == -1)
            printf("\nHijo: Error en cerrojo1");
        
        exit(EXIT_SUCCESS);

    }else{ // Padre
        sleep(2);

        if(fcntl(fd, F_SETLKW, &cerrojo2) == -1){
            printf("\nPadre: Error en cerrojo2");
        }else{
            printf("Padre: Cerrojo2 en el archivo\n");
        }
    }

    waitpid(-1, NULL, WNOHANG);
    return 0;
}