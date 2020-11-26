//tarea5.c
//Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10

#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
pid_t pid;
int estado;

if( (pid=fork()) < 0) {
	perror("\nError en el fork");
	exit(EXIT_FAILURE);
}
else if(pid==0) {  //proceso hijo ejecutando el programa
	if( (execl("/usr/bin/ldd","ldd","./tarea5")<0)) {
		perror("\nError en el execl");
		exit(EXIT_FAILURE);
	}
}
wait(&estado);
/*
<estado> mantiene información codificada a nivel de bit sobre el motivo de finalización del proceso hijo 
que puede ser el número de señal o 0 si alcanzó su finalización normalmente.
Mediante la variable estado de wait(), el proceso padre recupera el valor especificado por el proceso hijo como argumento de la llamada exit(), pero desplazado 1 byte porque el sistema incluye en el byte menos significativo 
el código de la señal que puede estar asociada a la terminación del hijo. Por eso se utiliza estado>>8 
de forma que obtenemos el valor del argumento del exit() del hijo.
*/

printf("\nMi hijo %d ha finalizado con el estado %d\n", pid, estado >> 8);

exit(EXIT_SUCCESS);

}

/*	El programa comienza creando un proceso hijo, el cual, comienza
	a ejecutarse a la vez del padre. Si falla muestra un error, sino, el 
	proceso hijo entra en el if y ejecuta dichos comandos.

	El comando execl hace que el proceso hijo no continue
	ejecutando las líneas de código siguiente y pase a ejecutar ek
	programa que le pasamos como argumento. En este caso, muestra las dependencias
	compartidas e este propio pograma

	Por otra parte, el padre espera 
	al hijo y recibe el estado con el que a finalizado el hijo.
*/

/*	   
	int execl(const char *pathname, const char *arg, ...
	Hay algunas funciones de la familia que reciben NULL como último arg para saber que
	acaban los argumentos
 

	   The  exec() family of functions replaces the current process image with
       a new process image.  The functions described in this manual  page  are
       front-ends  for execve(2).  (See the manual page for execve(2) for fur‐
       ther details about the replacement of the current process image.)

       The initial argument for these functions is the name of a file that  is
       to be executed.

       The  functions can be grouped based on the letters following the "exec"
       prefix.

   l - execl(), execlp(), execle()
       The const char *arg and subsequent ellipses can be thought of as  arg0,
       arg1, ..., argn.  Together they describe a list of one or more pointers
       to null-terminated strings that represent the argument  list  available
       to  the  executed  program.   The first argument, by convention, should
       point to the filename associated with the  file  being  executed.   The
       list  of  arguments  must  be  terminated by a null pointer, and, since
       these are variadic functions, this pointer must be cast (char *) NULL.
*/