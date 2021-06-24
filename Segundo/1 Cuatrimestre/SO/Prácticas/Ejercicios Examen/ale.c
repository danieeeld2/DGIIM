#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

static void handler(int sig) {
    int estado;

    sig = wait(&estado);
    printf("Ximo puto calvo %d con %d", sig, estado);
}

int main() {
    struct dirent *sitio;
    struct stat atributos;
    struct sigaction sig_USR_nact;
    struct flock cerrojo;
    DIR *directorio;
    int fd[2], leidos, fdnose;
    pid_t pid;
    char buffer[1024] ,*name;

    pipe(fd);
    sig_USR_nact.sa_handler = handler;
    sigemptyset(&sig_USR_nact.sa_mask);
    sig_USR_nact.sa_flags = 0;

    if ((pid = fork()) < 0) {
        perror("Error en el fork\n");
    }
    else if (pid == 0) {
        sleep(1);
        close(fd[1]);

        cerrojo.l_type = F_RDLCK;
        cerrojo.l_whence = SEEK_SET;
        cerrojo.l_start = 0;
        cerrojo.l_len = 0;

        while (leidos = read(fd[0], &buffer, sizeof(buffer)) > 0) {
            printf("%s", buffer);
            sleep(10);
            fdnose = open(buffer, O_RDONLY, NULL);
            

            if (fcntl(fdnose, F_SETLKW, &cerrojo) == -1) {
                perror("Problemas al crear el cerrojo");
                exit(1);
            }
            //execlp("cat", "cat", buffer, NULL);
            printf("\n");

            if (fcntl(fdnose, F_ULOCK, &cerrojo) == -1) {
                perror("Problemas al crear el cerrojo");
                exit(1);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else {
        close(fd[0]);
        directorio = opendir(".");

        if (sigaction(SIGPIPE, &sig_USR_nact, NULL) == -1) {
            perror("Error en el manejador de senal");
            exit(EXIT_FAILURE);
        }

        while ((sitio = readdir(directorio)) != 0) {
            umask(0);
            if (lstat(sitio->d_name, &atributos) < 0)
                perror("Error en lstat\n");

            if (S_ISREG(atributos.st_mode)) {
                if (atributos.st_mode != 0766)
                    chmod(sitio->d_name, 0766);

                write(fd[1], sitio->d_name, leidos);
                printf("El archivo %s tiene inodo %d\n", sitio->d_name, sitio->d_ino);
            }
        }
    }

    wait(NULL);
    return 0;
}