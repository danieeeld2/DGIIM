#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>

int main(int argc, char *argv[]){
	char *pathname;
	DIR *dir;
	unsigned int permisos;
	struct dirent *ed;
	struct stat atributos;
	char cadena[1000];
	char cadena2[2000];
	extern int errno;


	// Comprobamos que el número de argumentos es correcto
	if(argc != 3){
		printf("Error en los argumentos\n");
		printf("Uso: ejercicio.c <pathname> <permisos>\n");
		exit(-1);
	}

	pathname = argv[1];
	dir = opendir(pathname);
	permisos = strtol(argv[2], NULL, 8);	// Pasar el argumento a octal

	/*  long int strtol(const char *nptr, char **endptr, int base);
		
		The  strtol()  function converts the initial part of the string in nptr
        to a long integer value according to the given base, which must be  be‐
        tween 2 and 36 inclusive, or be the special value 0.
	*/

	if (dir == NULL){
		printf("ERROR, no se ha podido abrir el directorio\n");
		exit(-1);
	}

	readdir(dir);	// Lee el directorio
	ed=readdir(dir);	// Lee el archivo /. del directorio

	/* The  readdir()  function returns a pointer to a dirent structure repre‐
       senting the next directory entry in the directory stream pointed to  by
       dirp.   It  returns NULL on reaching the end of the directory stream or
       if an error occurred
    */

    while((ed=readdir(dir))!= 0){
    	sprintf(cadena, "%s/%s", pathname, ed->d_name);

    	/* La función spritnf formatea la cadena
    	   sprintf ( string $format [, mixed $args [, mixed $... ]] ) : string

    	   %* representa el formato. En nuestro caso, s significa que hace
    	   un formateo a string
    	*/

    	if(lstat(cadena, &atributos) < 0){
    		printf("\nError al intentar acceder a los atributos de la cadena ");
    		printf("%s\n",cadena);
    		perror("Error en lstat\n");
    		exit(-1);
    	}

    	if(S_ISREG(atributos.st_mode)){
    		sprintf(cadena2, "%s", ed->d_name);
    		printf("%s: %o ", cadena2, atributos.st_mode);	// %o formateo a octal

    		chmod(cadena, permisos);

    		if(chmod(cadena,permisos) < 0){
    			printf("Error: %s %o\n",cadena, permisos);

    			/* The strerror() function returns a pointer to a  string  that  describes
       			   the  error  code  passed  in  the  argument  errnum
				   
				   errno return number of last error
				   The  value  in  errno  is significant only when the return value of the
       			   call indicated an error

       			*/
    		}else{
    			stat(cadena,&atributos);
    			printf("%o \n",atributos.st_mode);
    		}
    	}
    }

    closedir(dir);

    return EXIT_SUCCESS;
}

