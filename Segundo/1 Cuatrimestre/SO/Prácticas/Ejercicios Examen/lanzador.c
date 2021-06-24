#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

int nclients;
int endclients = 0;

struct request {
	int number;
	int metadata;
	pid_t pid;
};

void handler()
{
	int estado;
	pid_t pid;

	pid = wait(&estado);

	printf("Mi hijo %d ha finalizado con estado %d\n", pid, estado);

	if (++endclients == (nclients * 2)) {
		unlink("FIFOpet");
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char **argv)
{
	int fdfifopet, fdfifochild, result, fdserver[2];
	char *pathname;
	pid_t pid;
	char namefifochild[1024];
	struct request r;
	char m;

	nclients = atoi(argv[1]);
	pathname = argv[2];

	srand((unsigned int) getpid());

	signal(SIGCHLD, handler);

	umask(0);
	mkfifo("FIFOpet", 0644);
	fdfifopet = open("FIFOpet", O_RDWR);

	for(int i = 0; i < nclients; i++) {
		if ((pid = fork()) == 0) {
			printf("Cliente %d: %d\n", i + 1, getpid());

			sprintf(namefifochild, "FIFO.%d", getpid());
			mkfifo(namefifochild, 0644);
			fdfifochild = open(namefifochild, O_RDWR);

			srand((unsigned int) getpid());
			r.number = rand() % 20 + 1; // [1,20]
			r.metadata = rand() % 2 + 1; // [1,2]
			r.pid = getpid();

			printf("Cliente envia: %d, %d, %d\n", r.number, r.metadata, r.pid);

			write(fdfifopet, &r, sizeof(r));
			read(fdfifochild, &result, sizeof(int));

			if (result == -1) {
				printf("Client %d: FALLO\n", getpid());
			} else {
				if (r.metadata == 1) {
					printf("Número de Inodo = %d\n", result);
				} else {
					printf("Tam Archivo = %d\n", result);
				}
			}

			unlink(namefifochild);

			exit(EXIT_SUCCESS);
		}
	}

	while(read(fdfifopet, &r, sizeof(r)) > 0) {
		printf("Padre recibe: %d, %d, %d\n", r.number, r.metadata, r.pid);

		pipe(fdserver);
		if (fork() == 0) {
			close(fdserver[1]);
			dup2(fdserver[0], STDIN_FILENO);
			execlp("./servidor", "servidor", pathname, NULL);
		} else {
			if (r.metadata == 1) {
				m = 'i';
			} else {
				m = 's';
			}

			close(fdserver[0]);
			write(fdserver[1], &r.number, sizeof(int));
			write(fdserver[1], &m, sizeof(char));
			write(fdserver[1], &r.pid, sizeof(int));
		}
	}
}
