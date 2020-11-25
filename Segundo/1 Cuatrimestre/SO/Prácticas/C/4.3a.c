#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    int num_procesos = 20;
    pid_t childpid;

    // Jerarquía tipo 1 //
    for (int i=1; i < num_procesos; i++){
        if ( (childpid = fork()) == -1){
            perror("\nNo pudo crearse el hijo\n");
            exit(-1);
        }

        if (childpid){	// Entra si chilpid > 0, es decir, entra el proceso padre
            printf("Padre: %d, proceso: %d\n", getppid(), getpid());
            break;
        }
    }
}

/*	En este caso, el proceso padre crea un proceso hijo, y éste un nuevo hijo suyo
	y así sucesivamente hasta completar el número de iteraciones. Esto se debe a que el
	proceso padre entra en el if y termina la ejecución de su bucle, pero el hijo
	no entra, luego pasa a la siguiente iteración y se convierte en proceso padre, así
	sucesivamente		
*/
