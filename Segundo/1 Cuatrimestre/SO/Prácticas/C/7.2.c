#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t PID;
    if( (strcmp(argv[2], "|")!=0) || (argc != 4) )
    {
        perror("Error en los argumentos\n");
        exit(-1);
    }
    pipe(fd); // Llamada al sistema para crear un pipe
    if ( (PID= fork())<0) {
        perror("fork");
        exit(-1);
    }
    if(PID == 0) { // ls
        //Establecer la dirección del flujo de datos en el cauce cerrando
        // el descriptor de lectura de cauce en el proceso hijo
        close(fd[0]);
        //Redirigir la salida estándar para enviar datos al cauce
        //--------------------------------------------------------
        //Cerrar la salida estándar del proceso hijo
        close(STDOUT_FILENO);
        //Duplicar el descriptor de escritura en cauce en el descriptor
        //correspondiente a la salida estándar (stdout)
        fcntl(fd[1], F_DUPFD, STDOUT_FILENO);
        execlp(argv[1], argv[1], NULL);
    }
    else { // sort. Estoy en el proceso padre porque PID != 0
        //Establecer la dirección del flujo de datos en el cauce cerrando
        // el descriptor de escritura en el cauce del proceso padre.
        close(fd[1]);
        //Redirigir la entrada estándar para tomar los datos del cauce.
        //Cerrar la entrada estándar del proceso padre
        close(STDIN_FILENO);
        //Duplicar el descriptor de lectura de cauce en el descriptor
        //correspondiente a la entrada estándar (stdin)
        fcntl(fd[0], F_DUPFD, STDIN_FILENO);
        execlp(argv[3], argv[3], NULL);
    }
    return(0);
}