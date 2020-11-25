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

        if (!childpid){	// Entra si chilpid es 0, es decir si es proceso hijo
            printf("Padre: %d, proceso: %d\n", getppid(), getpid());
            break;
        }
    }
}

/*  En este caso, el proceso padre crea muchos procesos hijos. Pero, al contrario
    del caso anterior, ningún hijo crea un nuevo proceso hijo.
    Esto se debe  que el proceso hijo tiene pid 0, luego entra en el if y el break
    acaba con la ejecución de su bucle, mientras que el proceso padre, al tener pid distinto
    de cero, nunca entrará en el if, por lo que realizará todas las iteraciones
*/
