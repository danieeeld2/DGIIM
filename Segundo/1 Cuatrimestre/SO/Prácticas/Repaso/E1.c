/*    Desarrolle un programa en C (ejercicio1.c) utilizando llamadas al sistema y haciendo uso de los mecanismos 
que considere oportunos para copiar los archivos regulares
 con tamaño superior o igual a 1 KB de un directorio (primer argumento) a otro directorio (segundo argumento). 
 Si no existe el directorio debe de crearse.

    Por cada archivo copiado, escribir una línea de caracteres en un fichero con nombre copiados.txt siguiendo el formato:
     nombre|permisos|tamaño. Un ejemplo del contenido del fichero sería:

           ejercicio.txt|677|10456

           datos.txt|777|34534*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char **argv){
    DIR *dir;
	struct dirent *ed;
	struct stat atributes;
    char *pathname;
    char archivo[1024];
    int fdout;
    char mensaje[1024];

    // Control de argumentos
    if (argc != 3){
        printf("El programa se ejecuta como: ./script <directorio1> <directorio2>\n");
        exit(-1);
    }

    pathname = argv[1];
    dir = opendir(argv[1]); // Abrimos el directorio
    if (dir == NULL){
        printf("Error, no se ha podido abrir el directorio\n");
        exit(-1);
    }

    umask(0);
    mkdir(argv[2], 0777);

    if((fdout=open("copia.txt",O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR)) < 0){
        printf("Error, no se ha podido abrir el archivo\n");
        exit(-1);
    }

    while((ed=readdir(dir)) != 0){ // Leemos el contenido del directorio
        if(strcmp(ed->d_name, ".") != 0 && strcmp(ed->d_name, "..") != 0){
            sprintf(archivo, "%s/%s", pathname, ed->d_name);    // Nombre del archivo que acabamos de leer
            lstat(archivo, &atributes); // Metadatos del archivo

            if(S_ISREG(atributes.st_mode)){ // Comprobamos si el archivo es regular
                if(atributes.st_size >= 1024){  // Si es mayor que 1KB
                    int tam = sprintf(mensaje,"%s|%o|%ld\n",ed->d_name,atributes.st_mode,atributes.st_size);
                    write(fdout, mensaje, tam);
                    execlp("cp", "cp", archivo, argv[2], NULL);
                }
            }
        }
    }

    close(fdout);
    closedir(dir);
    exit(EXIT_SUCCESS);
}