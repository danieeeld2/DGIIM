/*
tarea4.c
Trabajo con llamadas al sistema de Control de Procesos "POSIX 2.10 compliant"
Prueba el programa tal y como está. Después, elimina los comentarios (1) y
pruébalo de nuevo.
*/

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

int global=6;
char buf[]="cualquier mensaje de salida\n";

int main(int argc, char *argv[]){
	int var;
	pid_t pid;
	var=88;
	if(write(STDOUT_FILENO,buf,sizeof(buf)+1) != sizeof(buf)+1) {
		perror("\nError en write");
		exit(-1);
	}

	//(1)if(setvbuf(stdout,NULL,_IONBF,0)) {
	// 		perror("\nError en setvbuf");
	// }

	printf("\nMensaje previo a la ejecución de fork");

	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(-1);
	} else if(pid==0) {
		//proceso hijo ejecutando el programa
		global++;
		var++;
	} else{ //proceso padre ejecutando el programa
		sleep(1);
	printf("\npid= %d, global= %d, var= %d\n", getpid(),global,var);
	exit(0);
}
