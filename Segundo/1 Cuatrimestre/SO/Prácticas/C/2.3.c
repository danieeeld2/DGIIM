#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#define mymask(mode) ((mode) & ~S_IFMT)

// Permisos de ejecución para grupo y otros.
#define S_IFXGRPOTH 011

// Se define la macro con la regla para comprobar si tiene permiso x en grupo y otros
#define regla1(mode) ((((mode) & ~S_IFMT) & 011) == S_IFXGRPOTH)
    
    void buscar_dir(DIR *direct, char pathname[], int *reg, int *tamanio) {
        struct stat atributos;
        struct dirent *ed;
        DIR *direct_act;
        char cadena[500];

        while ((ed = readdir(direct)) != NULL){     // Leemos el directorio
            // Ignorar el directorio actual y el supoerior
            if (strcmp(ed->d_name, ".") != 0 && strcmp(ed->d_name, "..") != 0){
                sprintf(cadena, "%s/%s", pathname, ed->d_name); // Concatenamos el nombre del archivo con la ruta del directorio

                if (stat(cadena, &atributos) < 0){  // Almacenamos los metadatos del archivo
                    printf("\nError al intentar acceder a los atributos de archivo");
                    perror("\nError en lstat");
                    exit(-1);
                }

                if (S_ISDIR(atributos.st_mode)){    // Comprobamos si el archivo es un directorio
                    if ((direct_act = opendir(cadena)) == NULL) // Lo abrimos
                        printf("\nError al abrir el directorio: [%s]\n", cadena);
                    else
                        buscar_dir(direct_act, cadena, reg, tamanio);   // Llamada recursiva
                }else{
                    printf("%s %ld \n", cadena, atributos.st_ino);

                    if (S_ISREG(atributos.st_mode)){    // Miramos si es un archivo regular
                        if (regla1(atributos.st_mode)){ // Condicioner del ejercicio
                            (*reg)++;
                            (*tamanio) += (int)atributos.st_size;
                        }
                    }
                }
            }
        }
        closedir(direct);   // Cerramos el directorio
}
int main(int argc, char *argv[]){
    DIR *direct;
    char pathname[500];
    int reg = 0, tamanio = 0;

    if (argc == 2){
        strcpy(pathname, argv[1]);
    }else{
        strcpy(pathname, ".");
    }

    if ((direct = opendir(pathname)) == NULL){
        printf("\nError al abrir directorio\n");
        exit(-1);
    }

    printf("Los inodos son: \n\n");
    buscar_dir(direct, pathname, &reg, &tamanio);
    printf("Hay %d archivos regulares con permiso x para grupo y otros\n", reg);
    printf("El tamaño total ocupado por dichos archivos es %d bytes\n", tamanio);
    
    return 0;
}