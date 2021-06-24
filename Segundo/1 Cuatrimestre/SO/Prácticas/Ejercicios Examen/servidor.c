#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char **argv)
{
	int n, i = 0, error = -1, fdfifochild;
	pid_t pid;
	char metadata, pathname[1024], namefifochild[1024];
	DIR *dir;
	struct dirent *input;
	struct stat attributes;

	read(STDIN_FILENO, &n, sizeof(int));
	read(STDIN_FILENO, &metadata, sizeof(char));
	read(STDIN_FILENO, &pid, sizeof(int));

	sprintf(namefifochild, "FIFO.%d", pid);
	fdfifochild = open(namefifochild, O_RDWR);

	dir = opendir(argv[1]);
	while((input = readdir(dir))) {
		sprintf(pathname, "%s/%s", argv[1], input->d_name);
		lstat(pathname, &attributes);

		if (i == n && S_ISREG(attributes.st_mode)) {
			if (metadata == 'i') {
				write(fdfifochild, &attributes.st_ino, sizeof(int));
			} else {
				write(fdfifochild, &attributes.st_size, sizeof(int));
			}

			exit(EXIT_SUCCESS);
		}

		i++;
	}

	write(fdfifochild, &error, sizeof(int));

	exit(EXIT_SUCCESS);
}