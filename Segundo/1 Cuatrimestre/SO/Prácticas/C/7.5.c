#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SIZE 32768

void UsoIncorrento(){
    printf("La función debe llamarse así:\".ejercicio5.out <archivo> <directorio a copia>\"");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
    if(argc != 3)
        UsoIncorrento();;
    
    struct stat atributos1, atributos2;
    int fd1, fd2;
    char *ptr1, *ptr2, buf[256];

    umask(0);

    strcpy(buf, argv[2]);
    strcat(buf, "/");
    strcat(buf, argv[1]);

    if((fd1 = open(argv[1], O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0 ||
    (fd2 = open(buf, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0){
        printf("Error en el open\n");
        exit(EXIT_FAILURE);
    }

    if(fstat(fd1, &atributos1) == -1){
        printf("Error en el lstat 1");
        exit(EXIT_FAILURE);
    }

    if(!S_ISREG(atributos1.st_mode)){
        printf("El archivo no es regular\n");
        exit(EXIT_FAILURE);
    }

    if(ftruncate(fd2, atributos1.st_size) == -1){
        printf("Error en el ftruncate\n");
        exit(EXIT_FAILURE);
    }

    if(fstat(fd2, &atributos2) == -1){
        printf("Error en el lstat 2\n");
        exit(EXIT_FAILURE);
    }

    ptr1 = (char*) mmap(NULL, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd1, 0);

    if(ptr1 == MAP_FAILED){
        printf("Error en el map 1");
        exit(EXIT_FAILURE);
    }

    ptr2 = (char*) mmap(NULL, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd2, 0);

    if(ptr2 == MAP_FAILED){
        printf("Error en el map 2");
        exit(EXIT_FAILURE);
    }

    memcpy(ptr2, ptr1, atributos1.st_size);

    if(munmap(ptr1, atributos1.st_size) == -1){
        printf("Error al cerrar la proyección 1\n");
        exit(EXIT_FAILURE);
    }

    if(munmap(ptr2, atributos2.st_size) == -1){
        printf("Error al cerrar la proyección 2\n");
        exit(EXIT_FAILURE);
    }

    close(fd1);
    close(fd2);
    exit(EXIT_SUCCESS);
}