#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int cont[NSIG];

void handler(int signum)
{
	printf("Recibida la señal número %d, numero de veces %d\n", signum, ++cont[signum]);
}

int main(int argc, char *argv[])
{
	struct sigaction sa;
	int i;

	if(setvbuf(stdout, NULL, _IONBF, 0)){
    	perror("\nError en setvbuf");
    }

    sa.sa_handler = handler;

    for(i = 1; i < NSIG; i++) {
    	cont[i] = 0;
    	if (sigaction(i, &sa, NULL) < 0) {
    		printf("Error al intentar establecer el manejador de la señl %d\n", i);
    	}
    }

    while(1);
}