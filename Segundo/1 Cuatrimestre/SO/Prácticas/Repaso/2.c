#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[]){
    DIR *direct;
    unsigned int permisos;
    char *pathname;
    struct stat atributos;
    struct dirent *ed;
    char cadena[100];
    char cadena2[100];
    extern int errno;

    if (argc == 3){
        pathname = argv[1];
        direct = opendir(pathname);     // Abrimos el directorio
        permisos = strtol(argv[2], NULL, 8);    // Almacenamos los permisos

        /*  long int strtol(const char *nptr, char **endptr, int base);
		
		The  strtol()  function converts the initial part of the string in nptr
        to a long integer value according to the given base, which must be  be‐
        tween 2 and 36 inclusive, or be the special value 0.
	    */

    }else{
        printf("Uso: ejercicio2.c <pathname> <permisos>\n");
        exit(-1);
    }

    if(direct == NULL){
        printf("Error, no se ha podido abrir el directorio");
        exit(-1);
    }

    readdir(direct);    // Lee el direcotiro
    ed=readdir(direct);     // Lee el archivo /. del directorio

    /* The  readdir()  function returns a pointer to a dirent structure repre‐
       senting the next directory entry in the directory stream pointed to  by
       dirp.   It  returns NULL on reaching the end of the directory stream or
       if an error occurred
    */

    while ((ed = readdir(direct)) != 0){
        sprintf(cadena, "%s/%s", pathname, ed->d_name); // Concatenamos la ruta del directorio con el nombre del archivo

        if (stat(cadena, &atributos) < 0){  // Almacenamos los metadatos del archivo
            printf("\nError al intentar acceder a los atributos de archivo");
            perror("\nError en lstat");
            exit(-1);
        }
        if (S_ISREG(atributos.st_mode)){
            sprintf(cadena2, "%s", ed->d_name);
            printf("%s: %o ", cadena2, atributos.st_mode);
            chmod(cadena, permisos);
            if (chmod(cadena, permisos) < 0){   // Cambiamos los permisos
                printf("Error: %s\n", strerror(errno));
            }
            else{   // Si no se puede, imprimimos los anteriores
                stat(cadena, &atributos);
                printf("%o \n", atributos.st_mode);
            }
        }
    }

    closedir(direct);   // Cerramos el directorio
    return 0;
}