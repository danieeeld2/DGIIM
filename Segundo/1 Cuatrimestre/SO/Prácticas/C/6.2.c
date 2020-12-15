#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int seniales[_NSIG];	// cte con el numero de señales del sistema

void sig_USR_hdlr(int i) {
    seniales[i]++;
    printf("La señal %i ha sido recibida %i veces\n", i, seniales[i]);
}

int main(int argc, char *argv[])
   {
    struct sigaction sig_USR_nact;
    if(setvbuf(stdout,NULL,_IONBF,0)) 
       {    perror("\nError en setvbuf");
       }

//Inicializar la estructura sig_USR_na para especificar la nueva acción para la señal.

sig_USR_nact.sa_handler= sig_USR_hdlr;

//'sigemptyset' inicia el conjunto de señales dado al conjunto vacio. 

sigemptyset (&sig_USR_nact.sa_mask);
sig_USR_nact.sa_flags = 0;

for ( int i = 0; i < _NSIG; i++ )
	seniales[i] = 0;


for ( int i = 1; i < _NSIG && i != SIGSTOP && i != SIGKILL; i++ ) {
    if (sigaction(i, &sig_USR_nact, NULL) == -1) {
    	printf("No se pudo manejar %i\n", i);
    }
}

while(1);
}
