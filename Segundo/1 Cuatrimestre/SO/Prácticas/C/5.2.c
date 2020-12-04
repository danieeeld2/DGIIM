#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
int fd[2], numBytes;
pid_t PID;
char mensaje[]= "\nEl primer mensaje transmitido por un cauce!!\n";
char buffer[80];

pipe(fd); // Llamada al sistema para crear un cauce sin nombre

if ( (PID= fork())<0) {
	perror("fork");
	exit(EXIT_FAILURE);
}
if (PID == 0) {
	//Cierre del descriptor de lectura en el proceso hijo
	close(fd[0]);
	// Enviar el mensaje a traves del cauce usando el descriptor de escritura
	write(fd[1],mensaje,strlen(mensaje)+1);
	exit(EXIT_SUCCESS);
}
else { // Estoy en el proceso padre porque PID != 0
	//Cerrar el descriptor de escritura en el proceso padre
	close(fd[1]);
	//Leer datos desde el cauce.
	numBytes= read(fd[0],buffer,sizeof(buffer));
	printf("\nEl numero de bytes recibidos es: %d",numBytes);
	printf("\nLa cadena enviada a traves del cauce es: %s", buffer);
}

return EXIT_SUCCESS;
}

/*	PIPE(2)                    Linux Programmer's Manual                   PIPE(2)

	NAME
	       pipe, pipe2 - create pipe

	SYNOPSIS
	       #include <unistd.h>

	   pipe()  creates  a pipe, a unidirectional data channel that can be used
	   for interprocess communication.  The array pipefd is used to return two
	   file  descriptors  referring to the ends of the pipe.  pipefd[0] refers
	   to the read end of the pipe.  pipefd[1] refers to the write end of  the
	   pipe.   Data  written  to  the write end of the pipe is buffered by the
	   kernel until it is read from the read end of the pipe.  For further de‐
	   tails, see pipe(7).

   RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, errno  is  set
       appropriately, and pipefd is left unchanged.

       On Linux (and other systems), pipe() does not modify pipefd on failure.
       A requirement standardizing this behavior was  added  in  POSIX.1-2016.
       The  Linux-specific pipe2() system call likewise does not modify pipefd
       on failure.


*/

/*	En este programa creamos un cauce sin nombre mediante la llamada al sistema pipe. A 
	continuación, creamos el proceso hijo, mediante la llamada a fork para que herede el 
	contecto del padre. 

	En nuestro caso se van a pasar datos del hijo al padre, es decir, el hijo es el
	productor y el padre el consumidor. Por tanto, se cierra el descriptor de escritura
	del padre y el de lectura del hijo.
*/