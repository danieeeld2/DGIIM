#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

// Creamos las dos variables globales para facilitar su modificación
int regulares = 0;
int tam = 0;

// Función que nos piden
void buscar(DIR *dir, char *path);

int main(int argc, char *argv[]){
	DIR *dir;


	if(argc == 2){
		dir = opendir(argv[1]);
		buscar(dir, argv[1]);
	}
	else{
		dir = opendir(".");
		buscar(dir, ".");
	}

	printf("Existen %d archivos regulares con permiso x para grupos y otros\n", regulares);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n", tam);

	closedir(dir);

	return EXIT_SUCCESS;
}

void buscar(DIR *dir, char *path){
	struct dirent *entrada;
	char pathname[500];
	struct stat atributos;
	DIR *subdir;

	// Leemos el contenido del directorio 
	while((entrada = readdir(dir)) != 0){
		sprintf(pathname, "%s/%s", path, entrada->d_name);
		lstat(pathname, &atributos);

		if(S_ISREG(atributos.st_mode) && (atributos.st_mode & S_IXGRP) && (atributos.st_mode & S_IXOTH)){
			printf("%s %lo\n", pathname, atributos.st_ino);
			regulares++;
			tam += atributos.st_size;
		}
		else if(S_ISDIR(atributos.st_mode)){	// Hay que comprobar si es un directorio, porque sino trataría de abrir archivos de caracteres o bloques
			subdir = opendir(pathname);
			buscar(subdir, pathname);
		}
	}
}
