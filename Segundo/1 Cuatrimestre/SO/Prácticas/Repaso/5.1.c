/*
 envioSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilización de la llamada kill para enviar una señal:
 0: SIGTERM
 1: SIGUSR1
 2: SIGUSR2
  a un proceso cuyo identificador de proceso es PID.
 SINTAXIS: envioSignal [012] <PID> 
*/


#include <sys/types.h> //POSIX Standard: 2.6 Primitive System Data Types 
#include<limits.h> //Incluye <bits/posix1_lim.h> POSIX Standard: 2.9.2 //Minimum    //Values Added to <limits.h> y <bits/posix2_lim.h>
#include <unistd.h> //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
int main(int argc, char *argv[])
 {
          long int pid;
          int signal;
          if(argc<3) {
          printf("\nSintaxis de ejecucion: envioSignal [012] <PID>\n\n");
          exit(EXIT_FAILURE);
           }
         pid= strtol(argv[2],NULL,10);
         if(pid == LONG_MIN || pid == LONG_MAX) 
           {
         if(pid == LONG_MIN)
         printf("\nError por desbordamiento inferior LONG_MIN %ld",pid);
         else
            printf("\nError por desbordamiento superior LONG_MAX %ld",pid);
            perror("\nError en strtol");
            exit(EXIT_FAILURE);
           }
        signal=atoi(argv[1]);
        switch(signal) {
            case 0: //SIGTERM
            kill(pid,SIGTERM); break;
            case 1: //SIGUSR1
            kill(pid,SIGUSR1); break;
            case 2: //SIGUSR2
            kill(pid,SIGUSR2); break;
            default : // not in [012]
            printf("\n No puedo enviar ese tipo de senal"); 
              }
}

/*  El programa comienza comprobando que se reciben 3 argumentos. En caso
    de no recibirlos, devuelve un mensaje de error con el uso apropiado del programa.
    A continuación, almacena el segundo argumento en l variable pid, para pasar 
    a comprobar si este valor se deborda inferior o superiormente. En dicho caso, 
    devuelve un mensaje de error y finaliza el programa.
    En caso de que strtol haya funcionado, se continua almacenando el segundo argumento 
    en signal. A continuación, un bucle comprueba cual ha sido la señal recibida, y, en 
    funció de la misma, llama a la orden kill, la cual, permite enviar una
    señal a un proceso. En caso de que la señal pasada como parámetro no esté entre esos valores,
    muestra un mensaje por pantalla diciendo que no se pudo enviar la señal
    NAME
       kill - send a signal to a process
    SYNOPSIS
       kill [options] <pid> [...]
    DESCRIPTION
       The  default  signal  for kill is TERM.  Use -l or -L to list available
       signals.  Particularly useful signals include  HUP,  INT,  KILL,  STOP,
       CONT,  and  0.   Alternate  signals may be specified in three ways: -9,
       -SIGKILL or -KILL.  Negative PID values may be  used  to  choose  whole
       process  groups; see the PGID column in ps command output.  A PID of -1
       is special; it indicates all processes except the kill  process  itself
       and init.
    SIGTERM --> Señal de terminación
    SIGUSR1 --> Señal definida por el usuario (1)
    SIGUSR2 --> Señal definida por el usuario (2)
*/
