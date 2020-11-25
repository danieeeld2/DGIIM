#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[]){

	if(argc != 2){
		printf("El programa necesita como argumento un número entero\n");
		perror("Error en los parámetros\n");
		exit(-1);
	}

	pid_t pid;

	pid = fork();	// Creación de un proceso hijo a través de fork

	/*	NAME
       		fork - create a child process

		SYNOPSIS
	       #include <sys/types.h>
	       #include <unistd.h>

	       pid_t fork(void);

		DESCRIPTION
	       fork()  creates  a new process by duplicating the calling process.  The
	       new process is referred to as the child process.  The  calling  process
	       is referred to as the parent process.

	       The child process and the parent process run in separate memory spaces.
	       At the time of fork() both memory spaces have the same content.  Memory
	       writes,  file  mappings (mmap(2)), and unmappings (munmap(2)) performed
	       by one of the processes do not affect the other.
	*/

	/*	El fork hace que a partir de dicho punto el proceso padre
		y el del hijo ejecuten el código (usando el mismo contexto). El tiempo
		de ejecución para cada uno depende de lo que determine el
		sistema (wait)
	*/

	if(pid < 0){
		printf("Fallo en fork. Un PID debe ser un entero no negativo\n");
		perror("Fallo en el fork\n");
		exit(-1);
	}
	else{
		if(pid == 0){	// Significa que es un proceso hijo
			printf("Soy el proceso hijo y mi pid es: %d y el de mi padre es %d\n", getpid(), getppid());

			printf("Vamos a comprobar si el número es par o impar:\n");
			int numero = atoi(argv[1]);
			if((numero%2) == 1)
				printf("El número %d introducido es impar\n", numero);
			else
				printf("El número %d introducido es par\n", numero);
		}
		else if(pid > 0){	// Significa que es un proceso padre
			printf("Soy el proceso padre y mi pid es: %d y el de mi hijo es %d\n", getpid(), pid);

			printf("Vamos a comprobar si el número introducido es divisible por 4\n");
			int numero = atoi(argv[1]);
			if(numero%4 == 0)
				printf("El número %d introducido es divisible por 4\n", numero);
			else printf("El número %d introducido es indivisible por 4\n", numero);	
		}
	}

	/*	NAME
       		getpid, getppid - get process identification

		SYNOPSIS
	       #include <sys/types.h>
	       #include <unistd.h>

	       pid_t getpid(void);
	       pid_t getppid(void);

		DESCRIPTION
	       getpid() returns the process ID (PID) of the calling process.  (This is
	       often used by routines that generate unique temporary filenames.)

	       getppid() returns the process ID of the parent of the calling  process.
	       This will be either the ID of the process that created this process us‐
	       ing fork(), or, if that process has already terminated, the ID  of  the
	       process  to which this process has been reparented (either init(1) or a
	       "subreaper" process defined via the prctl(2) PR_SET_CHILD_SUBREAPER op‐
	       eration).
	*/

	return EXIT_SUCCESS;
}