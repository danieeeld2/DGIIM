#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){
	int fdin;
	int fdout;
	char string[] = "El número de bloque es %d\n";
	char buffer[80];
	char block[20];
	int i = 1;
	int leidos = 0;
	char output[strlen(string)+2];


	// Primero tenemos que hacer un control del número de argumentos que se toman
	if(argc == 2){
		if((fdin = open(argv[1], O_WRONLY, S_IRUSR|S_IWUSR)) < 0){	// Si es menos que 0 da fallo. Ver los flags em el guión
			printf("Error %d en open\n", errno);	// Mensaje de error
			perror("Error en open\n");
			exit(-1);	// Salimos del programa, devolviendo -1 (significa que ha fallado)
		}
	} else{
		fdin = STDIN_FILENO;	// Al escritor de entrada (fdin) le asignamos la entrada estándar de teclado
	}

	if((fdout = open("salida.txt", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR)) < 0){	// Ver flags en guión
		printf("Error %d en open\n", errno);
		perror("Error en open\n");
		exit(-1);
	}

	// Reservamos el espacio para escribir posteriormente la cadena , hasta que sepamos %d
	lseek(fdout, strlen(string)+2, SEEK_SET);	// Reservamos desde el inicio hasta lo que ocupa la cadena +2(para el número y \n)

	// Realizamos la lectura
	while(((leidos = read(fdin, buffer, 80)) != 0)){	// Leemos en bloques de 80, tal y como pide el ejercicio
		sprintf(block, "\nBloque %d\n", i);	// Mete dicha linea en la cadena bloque
		write(fdout, block, strlen(block));	// Escribimos block en el archivo de salida
		write(fdout, buffer, leidos);		// Escribimos los 80 bytes que habíamos leido previamente en el archivo de salida
		i++;					// Aumentamos el contador para leer el siguiente bloque
	}

	lseek(fdout, 0, SEEK_SET);	// Devolvemos el puntero al principio para escribir la línea que nos habíamos saltado
	sprintf(output, string, i-1);	// Concatena string y cambia %d por i-1 (El menos uno es para corregir el índice)
	write(fdout, output, strlen(output));	// Lo escribimos en el archivo de salida

	if(close(fdin) == -1){
		printf("Error %d en close\n", errno);
		perror("Error en close\n");
		exit(-1);
	}

	return EXIT_SUCCESS;
}
