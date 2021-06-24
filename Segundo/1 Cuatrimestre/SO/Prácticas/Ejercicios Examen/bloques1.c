#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int fd[2], leidos;
	char buffer[64];

	pipe(fd);
	for (int i = 0; i < argc; i++) {
		if ((pid = fork()) == 0) {
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execlp("du", "-k", argv[i], NULL);
		}
	}

	close(fd[1]);
	while((leidos = read(fd[0], buffer, sizeof(buffer))) > 0) {
		write(STDOUT_FILENO, buffer, leidos);
	}
}