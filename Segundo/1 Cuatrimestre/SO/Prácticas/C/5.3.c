#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]) 
{
int fd[2];
pid_t PID;

pipe(fd); // Llamada al sistema para crear un pipe

if ( (PID= fork())<0) {
	perror("fork");
	exit(EXIT_FAILURE);
}
if(PID == 0) { // ls
	//Establecer la direccion del flujo de datos en el cauce cerrando
	// el descriptor de lectura de cauce en el proceso hijo
	close(fd[0]);

	//Redirigir la salida estandar para enviar datos al cauce
	//--------------------------------------------------------
	//Cerrar la salida estandar del proceso hijo
	close(STDOUT_FILENO);

	//Duplicar el descriptor de escritura en cauce en el descriptor
	//correspondiente a la salida estandar (stdout)
	dup(fd[1]);
	execlp("ls","ls",NULL);
}
else { // sort. Estoy en el proceso padre porque PID != 0

	//Establecer la dirección del flujo de datos en el cauce cerrando
	// el descriptor de escritura en el cauce del proceso padre.
	close(fd[1]);

	//Redirigir la entrada estándar para tomar los datos del cauce.
	//Cerrar la entrada estándar del proceso padre
	close	(STDIN_FILENO);

	//Duplicar el descriptor de lectura de cauce en el descriptor
	//correspondiente a la entrada estándar (stdin)
	dup(fd[0]);
	execlp("sort","sort",NULL);
}

return EXIT_SUCCESS;
}

/*	Comenzamos creando un cauce sin nombre, mediante la llamada al sistema pipe.
	A continuación, creamos el proceso hijo, mediante la llamada a fork, parq ue herede
	el contexto del padre.

	En nuestro caso, el programa simulará la orden de terminal ls | sort. Para ello,
	el hijo se encargará de ejecutar la orden ls. Como solo nos interesa la salida, cerramos
	su descriptor de entrada. Además, nos interesa que la salida de la orden
	no salga por la salida estándar, por lo que cerramos la misma y, con la orden dup, duplicamos
	el descriptor de escritura. De esta forma, ahora la salida "estándar" será el cauce (fichero)
	temporal creado por la orden pipe.

	Por otro lado, el padre hace básicamente lo mismo. Es importante saber que la orden
	dup es bloqueante, sino podría ocurrir que el padre ejecutase la orden sort, antes de que el
	hijo ejecutara ls.

	NAME
       dup, dup2, dup3 - duplicate a file descriptor

	SYNOPSIS
       #include <unistd.h>

       int dup(int oldfd);
       int dup2(int oldfd, int newfd);

	DESCRIPTION
       The  dup() system call creates a copy of the file descriptor oldfd, us‐
       ing the lowest-numbered unused file descriptor for the new descriptor.

       After a successful return, the old and new file descriptors may be used
       interchangeably.   They  refer  to  the same open file description (see
       open(2)) and thus share file offset and file status flags; for example,
       if the file offset is modified by using lseek(2) on one of the file de‐
       scriptors, the offset is also changed for the other.
*/