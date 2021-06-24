#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int fd[2], leidos, n = 0, fdr;
	char buffer[64], name[1024], result[1024];

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
		sprintf(name, "dato_%d.txt", n);
		sprintf(result, "%s - %s", buffer, argv[n]);

		int fdr = open(name, O_CREAT|O_WRONLY|O_TRUNC, 0666); // rw-rw-rw-
		write(fdr, result, sizeof(result));

		write(STDOUT_FILENO, buffer, leidos);
		n++;
	}

	while(1);
}