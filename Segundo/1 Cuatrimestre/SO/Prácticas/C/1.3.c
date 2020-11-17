#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define S_ISREG2(mode) ((mode & S_IFMT) == S_IFREG)

/* Aqui lo que hemos hecho es definir una macro. Le pasamos un modo
y mediante una operación binaria se compara con la máscara del sistema. Si el resultado
da lugar a la máscara S_IFREG, significa que es regular, luego devuelve true, en caso contrario, devuelve false, que es justo lo que queremos
*/

int main(int argc, char *argv[]){
	struct stat atributes;
	
	// Control de argumentos
	if(argc != 2){
		printf("Error en el número de argumentos\n");
		exit(-1);
	}
	
	if(lstat(argv[1], &atributes) < 0){	// Almacenamos los metadatos
		printf("Error en lstat\n");
		exit(-1);
	}
	
	if(S_ISREG2(atributes.st_mode)){	// S_ISREG2 es la macro que hemos creado
		printf("Es regular\n");
	}else{
		printf("No es regular\n");
	}

	return EXIT_SUCCESS;	// También vale rturn 0
}

