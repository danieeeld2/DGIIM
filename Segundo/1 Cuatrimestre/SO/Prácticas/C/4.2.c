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
#include<stdlib.h>

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
	} else //proceso padre ejecutando el programa
		sleep(1);
	printf("\npid= %d, global= %d, var= %d\n", getpid(),global,var);
	exit(0);
}

/*	El programa declara una variable tipo entero y un buffer globales.
	A continuación, entra en el main y declara una nueva variable
	tipo entero y un pid. Asigna a var el valor 88 y escrbe mediante
	la llamada al sistema de la orden write, el contenido
	del buffer por salida estandar. Notemos que necesita el tamaño del buffer +1, porque 
	el compilador añade al final el \0, sino daría segmetation. En caso de que esta
	escritura falle, pues manda un mensaje de error.

	A continuación, imprime la línea 31 por pantalla. Después, utiliza la llamada
	a fork para crear un proceso hijo. En caso de que falle, entra en el primer if mostrando 
	un mensaje de error y finalizando el programa. En casocontrario, el proceso hijo entra en
	el primer if y aumenta el valor de global y var, mientras que el proceso padre
	entra en el segundo if y espera un segundo para pasar ambos a ejeutar la última
	línea de código.

	Resulta curioso que pese a que el proceso hijo ejecuta el código a partir del fork, ambos 
	procesos imprimen el mensaje previo por pantalla. Esto se debe a que el pirntf antes
	de mostrar el mensaje por pantalla lo almacena en un buffer. El mensaje no
	se mostrará por pantalla hasta que se ejecute la siguiente línea, pero en la siguiente
	línea se cre el proceso hijo, el cual, hereda el contexto del padre, incluido el buffer

	Si descomentamos las líneas anteriores, evitamos que se imprima dos veces, ya 
	que estamos matando el proceso
*/