#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
	// [minA, maxA], [minB, maxB]
	int minA, minB;
	int maxA, maxB;
	int fdE1[2], fdE2[2], fdM[2];
	pid_t PID1, PID2;
	int valor;

	if (argc != 3){
		printf("Sintaxis de ejecución: ./maestro <a> <b>\n");
		exit(-1);
	}

	minA = strtol(argv[1], NULL, 10);	// Convierte string a int
	maxB = strtol(argv[2], NULL, 10);	// Convierte string a int

	// Creación de los cauces sin nombre
	pipe(fdE1);
	pipe(fdE2);
	pipe(fdM);

	if((PID1 = fork()) == 0){
		// hijo 1 == esclavo 1
		// Cerramos los descrpitores del esclavo 2, ya que no se comunican entre ellos
		close(fdE2[0]);
		close(fdE2[1]);

		// Cerramos el resto de descriptores que no necesitemos
		close(fdE1[1]);
		close(fdM[0]);

		// Esclavo 1 --> Maestro
		// Usamos la llamada a dup2 para cerrar la E/S estándar y que se utilice el cauce
		dup2(fdE1[0], STDIN_FILENO);
		dup2(fdM[1], STDOUT_FILENO);

		execl("./esclavo", "esclavo", NULL);
	} else if((PID2 = fork()) == 0){
		// hijo 2 == esclavo 2
		// Cerramos los descrpitores del esclavo 1, ya que no se comunican entre ellos
		close(fdE1[0]);
		close(fdE1[1]);

		// Cerramos el resto de descriptores que no necesitemos
		close(fdE2[1]);
		close(fdM[0]);

		// Esclavo 1 --> Maestro
		// Usamos la llamada a dup2 para cerrar la E/S estándar y que se utilice el cauce
		dup2(fdE2[0], STDIN_FILENO);
		dup2(fdM[1], STDOUT_FILENO);

		execl("./esclavo", "esclavo", NULL);

	} else{
		// Padre
		close(fdE1[0]);
		close(fdE2[0]);

		// Calculamos el intervalo 
		maxA = (minA + maxB)/2;
		minB = maxA+1;

		// Escritura en el intervalo [minA, maxA] en el hijo 1 (esclavo1)
		write(fdE1[1], &minA, sizeof(int));
		write(fdE1[1], &maxA, sizeof(int));

		// Escritura en el intervalo [minB, maxB] en el hijo 2 (esclavo2)
		write(fdE2[1], &minB, sizeof(int));
		write(fdE2[1], &maxB, sizeof(int));

		while((read(fdM[0], &valor, sizeof(int))) != 0){
			printf("%d\n", valor);
		}
	}

	return EXIT_SUCCESS;

}